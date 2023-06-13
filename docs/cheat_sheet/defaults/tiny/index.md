---
layout: page
show_in_menu: false
disable_anchors: true
title: Tiny Mappings - win-vind
nav: Tiny Mappings
---

## GUI Normal Mode

### Mode Transition

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<esc-left>`, `<ctrl-]>`|[\<to_gui_normal\>]({{ site.url }}/cheat_sheet/functions/#to_gui_normal)|
|`<esc-down>`|[\<to_resident\>]({{ site.url }}/cheat_sheet/functions/#to_resident)|
|`:`|[\<to_command\>]({{ site.url }}/cheat_sheet/functions/#to_command)|
|`i`|[\<to_insert\>]({{ site.url }}/cheat_sheet/functions/#to_insert)|

### Mouse Movement

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<left>`, `h`, `<bs>`|[\<move_cursor_left\>]({{ site.url }}/cheat_sheet/functions/#move_cursor_left)|
|`<right>`, `<space>`, `l`|[\<move_cursor_right\>]({{ site.url }}/cheat_sheet/functions/#move_cursor_right)|
|`k`, `-`, `<up>`|[\<move_cursor_up\>]({{ site.url }}/cheat_sheet/functions/#move_cursor_up)|
|`<down>`, `j`, `+`|[\<move_cursor_down\>]({{ site.url }}/cheat_sheet/functions/#move_cursor_down)|

### Mouse Clicking

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`o`, `o`|[\<click_left\>]({{ site.url }}/cheat_sheet/functions/#click_left)|
|`a`, `a`|[\<click_right\>]({{ site.url }}/cheat_sheet/functions/#click_right)|

### Mouse Scrolling

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<c-k>`, `<c-y>`|[\<scroll_up\>]({{ site.url }}/cheat_sheet/functions/#scroll_up)|
|`<c-e>`, `<c-j>`|[\<scroll_down\>]({{ site.url }}/cheat_sheet/functions/#scroll_down)|
|`<c-u>`|[\<scroll_up_halfpage\>]({{ site.url }}/cheat_sheet/functions/#scroll_up_halfpage)|
|`<c-d>`|[\<scroll_down_halfpage\>]({{ site.url }}/cheat_sheet/functions/#scroll_down_halfpage)|
|`<c-b>`|[\<scroll_up_onepage\>]({{ site.url }}/cheat_sheet/functions/#scroll_up_onepage)|
|`<c-f>`|[\<scroll_down_onepage\>]({{ site.url }}/cheat_sheet/functions/#scroll_down_onepage)|
|`<c-h>`, `zh`|[\<scroll_left\>]({{ site.url }}/cheat_sheet/functions/#scroll_left)|
|`zl`, `<c-l>`|[\<scroll_right\>]({{ site.url }}/cheat_sheet/functions/#scroll_right)|
|`zh`|[\<scroll_left_halfpage\>]({{ site.url }}/cheat_sheet/functions/#scroll_left_halfpage)|
|`zl`|[\<scroll_right_halfpage\>]({{ site.url }}/cheat_sheet/functions/#scroll_right_halfpage)|

### Mouse Jumping

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<home>`, `^`, `0`|[\<jump_cursor_to_left\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_left)|
|`<end>`, `$`|[\<jump_cursor_to_right\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_right)|
|`gg`|[\<jump_cursor_to_top\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_top)|
|`g`|[\<jump_cursor_to_bottom\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_bottom)|
|`gm`|[\<jump_cursor_to_hcenter\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_hcenter)|
|`m`|[\<jump_cursor_to_vcenter\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_vcenter)|
|`t`|[\<jump_cursor_to_active_window\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_to_active_window)|

### Complex Mouse Controls

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`f`|[\<jump_cursor_with_keybrd_layout\>]({{ site.url }}/cheat_sheet/functions/#jump_cursor_with_keybrd_layout)|
|`fo`, `ff`|[\<easyclick\>]({{ site.url }}/cheat_sheet/functions/#easyclick)[\<click_left\>]({{ site.url }}/cheat_sheet/functions/#click_left)|
|`fa`|[\<easyclick\>]({{ site.url }}/cheat_sheet/functions/#easyclick)[\<click_right\>]({{ site.url }}/cheat_sheet/functions/#click_right)|
|`fm`|[\<easyclick\>]({{ site.url }}/cheat_sheet/functions/#easyclick)[\<click_mid\>]({{ site.url }}/cheat_sheet/functions/#click_mid)|
|`fh`|[\<easyclick\>]({{ site.url }}/cheat_sheet/functions/#easyclick)|
|`<ctrl-m>`|[\<gridmove\>]({{ site.url }}/cheat_sheet/functions/#gridmove)|

## Insert Mode

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<ctrl-]>`, `<esc-left>`|[\<to_gui_normal\>]({{ site.url }}/cheat_sheet/functions/#to_gui_normal)|
|`<f8>`|[\<to_instant_gui_normal\>]({{ site.url }}/cheat_sheet/functions/#to_instant_gui_normal)|
|`<esc-down>`|[\<to_resident\>]({{ site.url }}/cheat_sheet/functions/#to_resident)|

## Resident Mode

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`<esc-left>`|[\<to_gui_normal\>]({{ site.url }}/cheat_sheet/functions/#to_gui_normal)|
|`<esc-down>`|[\<to_resident\>]({{ site.url }}/cheat_sheet/functions/#to_resident)|
|`<esc-up>`|[\<to_insert\>]({{ site.url }}/cheat_sheet/functions/#to_insert)|

## Command Mode

### Mode Transition

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`guinormal`, `gn`|[\<to_gui_normal\>]({{ site.url }}/cheat_sheet/functions/#to_gui_normal)|
|`resident`|[\<to_resident\>]({{ site.url }}/cheat_sheet/functions/#to_resident)|
|`i`, `insert`|[\<to_insert\>]({{ site.url }}/cheat_sheet/functions/#to_insert)|

### System Commands

|**Trigger Commands**|**Called Commands**|
|:---:|:---:|
|`exit`|[\<exit\>]({{ site.url }}/cheat_sheet/functions/#exit)|
|`set`|[\<set\>]({{ site.url }}/cheat_sheet/functions/#set)|
|`{mode}map`|[\<{mode}map\>]({{ site.url }}/cheat_sheet/functions/#map)|
|`{mode}noremap`|[\<{mode}noremap\>]({{ site.url }}/cheat_sheet/functions/#noremap)|
|`{mode}unmap`|[\<{mode}unmap\>]({{ site.url }}/cheat_sheet/functions/#unmap)|
|`{mode}mapclear`|[\<{mode}mapclear\>]({{ site.url }}/cheat_sheet/functions/#mapclear)|
|`com`, `command`|[\<command\>]({{ site.url }}/cheat_sheet/functions/#command)|
|`delc`, `delcommand`|[\<delcommand\>]({{ site.url }}/cheat_sheet/functions/#delcommand)|
|`comclear`, `comc`|[\<comclear\>]({{ site.url }}/cheat_sheet/functions/#comclear)|
|`so`, `source`|[\<source\>]({{ site.url }}/cheat_sheet/functions/#source)|

<br>
<br>
## See also
- [tiny](../tiny)
- [small](../small)
- [normal](../normal)
- [big](../big)
- [huge](../huge)
<br>