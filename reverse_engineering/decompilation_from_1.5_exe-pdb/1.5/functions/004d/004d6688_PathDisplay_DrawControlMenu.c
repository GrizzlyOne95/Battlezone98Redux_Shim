/*
 * Entry: 004d6688
 * Name: PathDisplay::DrawControlMenu
 * Namespace: PathDisplay
 * Signature: void DrawControlMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawControlMenu(PathDisplay *this)

{
  MenuMode MVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  ControlMode CVar5;
  PathDisplay *local_c;
  PathDisplay *local_8;
  
  MVar1 = this->menuMode;
  lVar3 = DisplayInterface::colorWhite;
  if ((MVar1 != MENU_CONTROL) && (lVar3 = DisplayInterface::colorGreen, MVar1 != MENU_NONE)) {
    lVar3 = DisplayInterface::colorGrey;
  }
  CVar5 = CONTROL_PLAN;
  if (MVar1 == MENU_NONE) {
    iVar2 = this[1]._padding_ + 1;
  }
  else {
    iVar2 = 0;
  }
  local_c = this;
  local_8 = this;
  DrawKeyItem(this,0x14,10,iVar2,"Control",lVar3,DisplayInterface::colorBlack);
  iVar2 = 0x1a;
  if (this->menuMode == MENU_CONTROL) {
    do {
      iVar4 = iVar2;
      lVar3 = DisplayInterface::colorYellow;
      if (CVar5 != this->controlMode) {
        lVar3 = DisplayInterface::colorGreen;
      }
      DrawKeyItem(this,0x14,iVar4,this[1]._padding_ + 1 + CVar5,controlText[CVar5],lVar3,
                  DisplayInterface::colorBlack);
      if (command_controls.mode_select[CVar5 + CONTROL_PATH] != '\0') {
        this->menuMode = MENU_NONE;
        this->nextControlMode = CVar5;
      }
      CVar5 = CVar5 + CONTROL_PATH;
      iVar2 = iVar4 + 0xb;
    } while ((int)CVar5 < 4);
    DrawKeyItem(this,0x14,iVar4 + 0x10,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                DisplayInterface::colorBlack);
    if (command_controls.menu_back != '\0') {
      this->menuMode = MENU_NONE;
    }
  }
  else {
    Graphic_Text(DisplayInterface::currentBuffer,0x14,0x1a,(long *)&local_c,(long *)&local_8,
                 controlText[this->controlMode],DisplayInterface::textFont,
                 DisplayInterface::colorWhite,DisplayInterface::colorBlack,0,0,0);
  }
  return;
}
