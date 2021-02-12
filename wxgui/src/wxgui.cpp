#include "wxgui.hpp"

#include <windows.h>

#include <atomic>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "disable_gcc_warning.hpp"
#include <wx/cmdline.h>
#include <wx/defs.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/taskbar.h>
#include <wx/thread.h>

#include <nlohmann/json.hpp>

#include "enable_gcc_warning.hpp"

#include "utility.hpp"
#include "wx_prop_dlg.hpp"
#include "io_params.hpp"
#include "msg_logger.hpp"
#include "path.hpp"

#include "win_vind.hpp"

namespace wxGUI
{
    inline static void error_box(const wxString& msg) {
        wxMessageBox(msg, wxT("Error - win-vind"), wxOK | wxICON_EXCLAMATION) ;
    }

    inline static bool is_pre_initialized() {
        std::ifstream ifs(Path::ROOT_PATH() + "is_initialized") ;
        if(!ifs.is_open()) {
            return false ;
        }
        std::string str{} ;
        std::getline(ifs, str) ;
        return str.front() == 'y' || str.front() == 'Y' ;
    }

    inline static void finish_pre_initialization() {
        std::ofstream ofs(Path::ROOT_PATH() + "is_initialized", std::ios::trunc) ;
        ofs << "y" ;
    }

    inline static bool initialize_config_files() ;

    static std::atomic_bool runnable{true} ;

    //core system is wrought at another thread
    class SystemThread : public wxThread {
    private:
        virtual ExitCode Entry() override {
            while(win_vind::update() && runnable.load()) ;
            return static_cast<ExitCode>(0) ;
        }

    public:
        SystemThread()
        : wxThread(wxTHREAD_DETACHED)
        {}
    } ;

    static std::string g_function_name{} ;

    void App::OnInitCmdLine(wxCmdLineParser& parser) {
        parser.AddOption(wxT("f"), wxT("func"),
                wxT("FunctionName"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL) ;
    }
    bool App::OnCmdLineParsed(wxCmdLineParser& parser) {
        wxString fn ;
        if(parser.Found(wxT("func"), &fn)) {
            g_function_name = fn.ToStdString() ;
        }
        return true ;
    }

    bool App::OnInit() {
        try {
            if(!wxApp::OnInit()) {
                return false ;
            }

            if(!wxTaskBarIcon::IsAvailable()) {
                wxMessageBox(
                        wxT("Not supported System Tray"),
                        wxT("Warning - win-vind"), wxOK | wxICON_EXCLAMATION) ;
            }

            if(!is_pre_initialized()) {
                if(!initialize_config_files()) {
                    return false ;
                }
            }

            if(!win_vind::initialize(g_function_name)) {
                return false ;
            }
            if(!ioParams::initialize()) {
                ERROR_PRINT("Failed initialize ioParams.") ;
                return false ;
            }

            auto ppd = new PropDlg() ;
            ppd->Show(false) ;

            //enable opening window by command
            win_vind::register_show_window_func([ppd] {
                ppd->Show(true) ;
            }) ;

            win_vind::register_exit_window_func([ppd] {
                ppd->Show(true) ;
                ppd->Destroy() ;
            }) ;
        }
        catch(const std::exception& e) {
            ERROR_PRINT(e.what()) ;
        }
        return true ;
    }

    int App::MainLoop() {
        //create a new thread for back-ground system
        auto pst = std::make_unique<SystemThread>() ;
        pst->Run() ;

        return wxApp::MainLoop() ;
    }

    App::~App() noexcept {
        if(runnable.load()) {
            //Core-win_vind is running
            runnable.store(false) ; //terminate core system
        }
    }

    bool App::OnExceptionInMainLoop() {
        try {
            throw ; //Rethrow the current exception.
        }
        catch(const std::exception& e) {
            ERROR_PRINT(e.what()) ;
        }

        return false ; //exit program
    }

    void App::OnUnhandledException() {
        try {
            throw ; //Rethrow the current exception.
        }
        catch(const std::exception& e) {
            ERROR_PRINT(e.what()) ;
        }
        //the program is already about to exit.
    }

    inline static bool initialize_config_files() {
        auto overwrite_bindings = [] {
            if(!CopyFileA(Path::Default::BINDINGS().c_str(), Path::BINDINGS().c_str(), FALSE)) {
                throw std::runtime_error("Could not overwrite " + Path::BINDINGS() + ".") ;
            }
        } ;
        auto overwrite_settings = [] {
            if(!CopyFileA(Path::Default::SETTINGS().c_str(), Path::SETTINGS().c_str(), FALSE)) {
                throw std::runtime_error("Could not overwrite " + Path::SETTINGS() + ".") ;
            }
        } ;

        auto write_kmp = [] (BOOL allow_overwrite) {
            //The kmp file needs a better format and a dedicated management system.
            std::vector<const char*> def_kmp = {
                "default_config/JP.kmp",
                "default_config/US.kmp",
                "default_config/custom.kmp"
            } ;
            std::vector<std::string> kmp = {
                Path::CONFIG_PATH() + "JP.kmp",
                Path::CONFIG_PATH() + "US.kmp",
                Path::CONFIG_PATH() + "custom.kmp"
            } ;

            for(std::size_t i = 0 ; i < def_kmp.size() ; i ++) {
                CopyFileA(def_kmp[i], kmp[i].c_str(), !allow_overwrite) ;
            }
        } ;

        try {
            if(!Utility::is_existed_dir(Path::CONFIG_PATH().c_str())) { //clean install
                if(!CreateDirectoryA(Path::CONFIG_PATH().c_str(), NULL)) {
                    throw std::runtime_error("Could not create a directory for settings.") ;
                }
                overwrite_bindings() ;
                overwrite_settings() ;
                write_kmp(TRUE) ;
            }
            else { //a config directory is already existed.
                auto answer = wxMessageBox(
                        wxT("The old configuration files are detected. "\
                            "Do you want to keep the configuration? "\
                            "If you cancel, will terminate win-vind and ask again the next time."),
                        wxT("Confirm - win-vind"), wxYES_NO | wxCANCEL) ;

                if(answer == wxCANCEL) return false ;

                if(answer == wxYES) { //keep
                    auto keep_old_and_only_write_new = [] (
                            const auto& default_path,
                            const auto& new_path,
                            auto& old_ifs) {
                        using json = nlohmann::json ;

                        json dfj ;
                        std::ifstream def_ifs(default_path) ;
                        def_ifs >> dfj ; //keep old

                        json olj ;
                        old_ifs >> olj ; 

                        if(dfj.is_object() && olj.is_object()) {
                            dfj.update(olj) ; //overwrite differences
                        }
                        else if(dfj.is_array() && olj.is_array()) {
                            for(auto& obj : dfj) {
                                for(auto& old : olj) {
                                    try {
                                        if(obj.at("name") == old.at("name")) {
                                            obj.update(old) ;
                                            break ;
                                        }
                                    }
                                    catch(const json::out_of_range&) {
                                        continue ;
                                    }
                                }
                            }
                        }
                        else {
                            throw std::runtime_error("The format of " + new_path + " is not supported.") ;
                        }

                        std::ofstream ofs(new_path) ;
                        ofs << std::setw(4) << dfj << std::endl ;
                    } ;

                    //bindings.json
                    std::ifstream bindings_ifs(Path::BINDINGS()) ;
                    if(!bindings_ifs.is_open()) {
                        overwrite_bindings() ; //does not exist
                    }
                    else {
                        keep_old_and_only_write_new(
                                Path::Default::BINDINGS(),
                                Path::BINDINGS(),
                                bindings_ifs) ;
                    }

                    //settings.json
                    std::ifstream settings_ifs(Path::SETTINGS()) ;
                    if(!settings_ifs.is_open()) {
                        overwrite_settings() ; //does not exist
                    }
                    else {
                        keep_old_and_only_write_new(
                                Path::Default::SETTINGS(),
                                Path::SETTINGS(),
                                settings_ifs) ;
                    }

                    //JP.kmp, US.kmp. custom.kmp
                    write_kmp(FALSE) ; //If a old file exist, not overwrite.
                }
                else { //overwrite
                    overwrite_bindings() ;
                    overwrite_settings() ;
                    write_kmp(TRUE) ;
                }

            }
        }
        catch(const std::exception& e) {
            error_box(wxString(e.what())
                    + wxT(", so could not create setting files of win-vind, so terminate.")) ;
            return false ;
        }

        finish_pre_initialization() ;
        return true ;
    }
}