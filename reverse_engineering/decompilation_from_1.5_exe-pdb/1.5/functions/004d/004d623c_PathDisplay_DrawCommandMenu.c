/*
 * Entry: 004d623c
 * Name: PathDisplay::DrawCommandMenu
 * Namespace: PathDisplay
 * Signature: void DrawCommandMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DrawCommandMenu(PathDisplay *this)

{
  MenuMode MVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long local_98;
  long local_94;
  Team *local_90;
  Team *local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  MVar1 = this->menuMode;
  lVar3 = DisplayInterface::colorWhite;
  if (((MVar1 == MENU_COMMAND) ||
      (lVar3 = DisplayInterface::colorGrey, lVar4 = DisplayInterface::colorGreen, MVar1 != MENU_NONE
      )) && (lVar4 = lVar3, MVar1 != MENU_NONE)) {
    iVar2 = 0;
  }
  else {
    iVar2 = this[1]._padding_ + 4;
    lVar3 = lVar4;
  }
  DrawKeyItem(this,0x104,10,iVar2,"Resource",lVar3,DisplayInterface::colorBlack);
  if (this->menuMode == MENU_COMMAND) {
    local_90 = Team::GetTeam(1);
    local_8c = Team::GetTeam(2);
    if (command_controls.mode_select[1] != '\0') {
      Team::AddScrap(local_90,((command_controls.cmd_multi == '\0') - 1 & 9) + 1);
    }
    if (command_controls.mode_select[2] != '\0') {
      Team::AddScrap(local_90,((command_controls.cmd_multi == '\0') - 1 & 0xfffffff7) - 1);
    }
    lVar3 = Team::GetMaxScrap(local_90);
    lVar4 = Team::GetScrap(local_90);
    sprintf(local_88,"Team 1 Scrap: %d/%d",lVar4,lVar3);
    Graphic_Text(DisplayInterface::currentBuffer,0x104,0x1a,&local_98,&local_94,local_88,
                 DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,0,0,0);
    DrawKeyItem(this,0x104,0x25,this[1]._padding_ + 1,"Add Scrap",DisplayInterface::colorGreen,
                DisplayInterface::colorBlack);
    DrawKeyItem(this,0x104,0x30,this[1]._padding_ + 2,"Sub Scrap",DisplayInterface::colorGreen,
                DisplayInterface::colorBlack);
    if (command_controls.mode_select[3] != '\0') {
      Team::AddPilot(local_90,((command_controls.cmd_multi == '\0') - 1 & 9) + 1);
    }
    if (command_controls.mode_select[4] != '\0') {
      Team::AddPilot(local_90,((command_controls.cmd_multi == '\0') - 1 & 0xfffffff7) - 1);
    }
    lVar3 = Team::GetMaxPilot(local_90);
    lVar4 = Team::GetPilot(local_90);
    sprintf(local_88,"Team 1 Pilots: %d/%d",lVar4,lVar3);
    Graphic_Text(DisplayInterface::currentBuffer,0x104,0x40,&local_98,&local_94,local_88,
                 DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,0,0,0);
    DrawKeyItem(this,0x104,0x4b,this[1]._padding_ + 3,"Add Pilot",DisplayInterface::colorGreen,
                DisplayInterface::colorBlack);
    DrawKeyItem(this,0x104,0x56,this[1]._padding_ + 4,"Sub Pilot",DisplayInterface::colorGreen,
                DisplayInterface::colorBlack);
    if (command_controls.mode_select[5] != '\0') {
      Team::AddScrap(local_8c,((command_controls.cmd_multi == '\0') - 1 & 9) + 1);
    }
    if (command_controls.mode_select[6] != '\0') {
      Team::AddScrap(local_8c,((command_controls.cmd_multi == '\0') - 1 & 0xfffffff7) - 1);
    }
    lVar3 = Team::GetMaxScrap(local_8c);
    lVar4 = Team::GetScrap(local_8c);
    sprintf(local_88,"Team 2 Scrap: %d/%d",lVar4,lVar3);
    Graphic_Text(DisplayInterface::currentBuffer,0x104,0x66,&local_98,&local_94,local_88,
                 DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,0,0,0);
    DrawKeyItem(this,0x104,0x71,this[1]._padding_ + 5,"Add Scrap",DisplayInterface::colorRed,
                DisplayInterface::colorBlack);
    DrawKeyItem(this,0x104,0x7c,this[1]._padding_ + 6,"Sub Scrap",DisplayInterface::colorRed,
                DisplayInterface::colorBlack);
    if (command_controls.mode_select[7] != '\0') {
      Team::AddPilot(local_8c,((command_controls.cmd_multi == '\0') - 1 & 9) + 1);
    }
    if (command_controls.mode_select[8] != '\0') {
      Team::AddPilot(local_8c,((command_controls.cmd_multi == '\0') - 1 & 0xfffffff7) - 1);
    }
    lVar3 = Team::GetMaxPilot(local_8c);
    lVar4 = Team::GetPilot(local_8c);
    sprintf(local_88,"Team 2 Pilots: %d/%d",lVar4,lVar3);
    Graphic_Text(DisplayInterface::currentBuffer,0x104,0x8c,&local_98,&local_94,local_88,
                 DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,0,0,0);
    DrawKeyItem(this,0x104,0x97,this[1]._padding_ + 7,"Add Pilot",DisplayInterface::colorRed,
                DisplayInterface::colorBlack);
    DrawKeyItem(this,0x104,0xa2,this[1]._padding_ + 8,"Sub Pilot",DisplayInterface::colorRed,
                DisplayInterface::colorBlack);
    DrawKeyItem(this,0x104,0xb2,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                DisplayInterface::colorBlack);
    if (command_controls.menu_back != '\0') {
      this->menuMode = MENU_NONE;
    }
  }
  return;
}
