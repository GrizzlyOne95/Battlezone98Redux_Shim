/*
 * Entry: 004d60c3
 * Name: PathDisplay::DrawColorMenu
 * Namespace: PathDisplay
 * Signature: void DrawColorMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DrawColorMenu(PathDisplay *this)

{
  MenuMode MVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  long local_94;
  int local_90;
  int local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  MVar1 = this->menuMode;
  lVar3 = DisplayInterface::colorWhite;
  if ((MVar1 != MENU_COLOR) && (lVar3 = DisplayInterface::colorGreen, MVar1 != MENU_NONE)) {
    lVar3 = DisplayInterface::colorGrey;
  }
  if (MVar1 == MENU_NONE) {
    iVar2 = this[1]._padding_ + 2;
  }
  else {
    iVar2 = 0;
  }
  DrawKeyItem(this,100,10,iVar2,"Draw",lVar3,DisplayInterface::colorBlack);
  iVar5 = 0;
  local_8c = 0x1a;
  iVar2 = local_8c;
  if (this->menuMode == MENU_COLOR) {
    do {
      local_8c = iVar2;
      uVar4 = 1 << ((byte)iVar5 & 0x1f);
      lVar3 = DisplayInterface::colorYellow;
      if ((this->colorMode & uVar4) == 0) {
        lVar3 = DisplayInterface::colorGreen;
      }
      DrawKeyItem(this,100,local_8c,this[1]._padding_ + 1 + iVar5,colorText[iVar5],lVar3,
                  DisplayInterface::colorBlack);
      if (command_controls.mode_select[iVar5 + 1] != '\0') {
        this->colorMode = this->colorMode ^ uVar4;
        this->menuMode = MENU_NONE;
      }
      iVar5 = iVar5 + 1;
      iVar2 = local_8c + 0xb;
    } while (iVar5 < 9);
    iVar2 = local_8c + 0x10;
    local_8c = local_8c + 0xb;
    DrawKeyItem(this,100,iVar2,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                DisplayInterface::colorBlack);
    if (command_controls.menu_back != '\0') {
      this->menuMode = MENU_NONE;
    }
  }
  else {
    do {
      if ((this->colorMode & 1 << ((byte)iVar5 & 0x1f)) != 0) {
        sprintf(local_88,"%s",colorText[iVar5]);
        Graphic_Text(DisplayInterface::currentBuffer,100,local_8c,&local_94,&local_90,local_88,
                     DisplayInterface::textFont,DisplayInterface::colorWhite,
                     DisplayInterface::colorBlack,0,0,0);
        local_8c = local_90 + 2;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 9);
  }
  return;
}
