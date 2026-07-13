/*
 * Entry: 004d7126
 * Name: PathDisplay::DrawEditMenu
 * Namespace: PathDisplay
 * Signature: void DrawEditMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawEditMenu(PathDisplay *this)

{
  MenuMode MVar1;
  int iVar2;
  char *pcVar3;
  long lVar4;
  long lVar5;
  PathDisplay *local_c;
  PathDisplay *local_8;
  
  MVar1 = this->menuMode;
  lVar4 = DisplayInterface::colorWhite;
  if (((MVar1 == MENU_EDIT) ||
      (lVar4 = DisplayInterface::colorGrey, lVar5 = DisplayInterface::colorGreen, MVar1 != MENU_NONE
      )) && (lVar5 = lVar4, MVar1 != MENU_NONE)) {
    iVar2 = 0;
  }
  else {
    iVar2 = this[1]._padding_ + 3;
    lVar4 = lVar5;
  }
  local_c = this;
  local_8 = this;
  DrawKeyItem(this,0xb4,10,iVar2,"Edit",lVar4,DisplayInterface::colorBlack);
  if (this->menuMode == MENU_EDIT) {
    lVar4 = DisplayInterface::colorYellow;
    if ((UserProfilePtr->playOption & 1) == 0) {
      lVar4 = DisplayInterface::colorGreen;
    }
    DrawKeyItem(this,0xb4,0x1a,this[1]._padding_ + 1,"On",lVar4,DisplayInterface::colorBlack);
    if (command_controls.mode_select[1] != '\0') {
      UserProfilePtr->playOption = UserProfilePtr->playOption | 1;
      this->menuMode = MENU_NONE;
    }
    lVar4 = DisplayInterface::colorGreen;
    if ((UserProfilePtr->playOption & 1) == 0) {
      lVar4 = DisplayInterface::colorYellow;
    }
    DrawKeyItem(this,0xb4,0x25,this[1]._padding_ + 2,"Off",lVar4,DisplayInterface::colorBlack);
    if (command_controls.mode_select[2] != '\0') {
      UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffe;
      this->menuMode = MENU_NONE;
    }
    DrawKeyItem(this,0xb4,0x35,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                DisplayInterface::colorBlack);
    if (command_controls.menu_back != '\0') {
      this->menuMode = MENU_NONE;
    }
  }
  else {
    pcVar3 = "On";
    if ((UserProfilePtr->playOption & 1) == 0) {
      pcVar3 = "Off";
    }
    Graphic_Text(DisplayInterface::currentBuffer,0xb4,0x1a,(long *)&local_c,(long *)&local_8,pcVar3,
                 DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,0,0,0);
  }
  return;
}
