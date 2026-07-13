/*
 * Entry: 004d7289
 * Name: PathDisplay::DrawMenuBar
 * Namespace: PathDisplay
 * Signature: void DrawMenuBar(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawMenuBar(PathDisplay *this)

{
  if (this->menuMode == MENU_NONE) {
    if (command_controls.mode_select[1] == '\0') {
      if (command_controls.mode_select[2] == '\0') {
        if (command_controls.mode_select[3] == '\0') {
          if (command_controls.mode_select[4] == '\0') {
            if (command_controls.mode_select[5] == '\0') {
              if (command_controls.mode_select[6] != '\0') {
                this->menuMode = MENU_TEAM;
                command_controls.mode_select[6] = '\0';
              }
            }
            else {
              this->menuMode = MENU_BUILD;
              command_controls.mode_select[5] = '\0';
            }
          }
          else {
            this->menuMode = MENU_COMMAND;
            command_controls.mode_select[4] = '\0';
          }
        }
        else {
          this->menuMode = MENU_EDIT;
          command_controls.mode_select[3] = '\0';
        }
      }
      else {
        this->menuMode = MENU_COLOR;
        command_controls.mode_select[2] = '\0';
      }
    }
    else {
      this->menuMode = MENU_CONTROL;
      command_controls.mode_select[1] = '\0';
    }
  }
  DrawControlMenu(this);
  DrawColorMenu(this);
  DrawEditMenu(this);
  DrawCommandMenu(this);
  DrawBuildMenu(this);
  DrawTeamMenu(this);
  return;
}
