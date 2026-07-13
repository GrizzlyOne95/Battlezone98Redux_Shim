/*
 * Entry: 004d6e1e
 * Name: PathDisplay::DrawTeamMenu
 * Namespace: PathDisplay
 * Signature: void DrawTeamMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DrawTeamMenu(PathDisplay *this)

{
  MenuMode MVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  long local_34;
  long local_30;
  int local_2c;
  char local_28 [16];
  char local_18 [8];
  char *local_10;
  char *local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  MVar1 = this->menuMode;
  lVar3 = DisplayInterface::colorWhite;
  if (((MVar1 == MENU_CONTROL) ||
      (lVar3 = DisplayInterface::colorGrey, lVar4 = DisplayInterface::colorGreen, MVar1 != MENU_NONE
      )) && (lVar4 = lVar3, MVar1 != MENU_NONE)) {
    iVar2 = 0;
  }
  else {
    iVar2 = this[1]._padding_ + 6;
    lVar3 = lVar4;
  }
  DrawKeyItem(this,0x1a4,10,iVar2,"Team",lVar3,DisplayInterface::colorBlack);
  local_2c = 0x1a;
  if (this->menuMode == MENU_TEAM) {
    if (this->teamMode == TEAM_NORMAL) {
      iVar2 = 1;
      do {
        sprintf(local_18,"Team %d",iVar2);
        lVar3 = DisplayInterface::colorYellow;
        if (this->buildTeam != iVar2) {
          lVar3 = DisplayInterface::colorGreen;
        }
        DrawKeyItem(this,0x1a4,local_2c,this[1]._padding_ + iVar2,local_18,lVar3,
                    DisplayInterface::colorBlack);
        iVar5 = local_2c;
        local_2c = local_2c + 0xb;
        if (command_controls.mode_select[iVar2] != '\0') {
          this->menuMode = MENU_NONE;
          this->buildTeam = iVar2;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 8);
      DrawKeyItem(this,0x1a4,local_2c,this[1]._padding_ + 8,"More...",DisplayInterface::colorGreen,
                  DisplayInterface::colorBlack);
      iVar5 = iVar5 + 0x16;
      if (command_controls.mode_select[8] != '\0') {
        this->teamMode = TEAM_EXTENDED;
      }
    }
    else {
      local_c = (char *)0x1;
      iVar2 = 8;
      do {
        sprintf(local_28,"Team %d",iVar2);
        lVar3 = DisplayInterface::colorYellow;
        if (this->buildTeam != iVar2) {
          lVar3 = DisplayInterface::colorGreen;
        }
        DrawKeyItem(this,0x1a4,local_2c,(int)(local_c + this[1]._padding_),local_28,lVar3,
                    DisplayInterface::colorBlack);
        iVar5 = local_2c + 0xb;
        if (command_controls.cmd_click[iVar2 + 1] != '\0') {
          this->teamMode = TEAM_NORMAL;
          this->menuMode = MENU_NONE;
          this->buildTeam = iVar2;
        }
        local_c = local_c + 1;
        iVar2 = iVar2 + 1;
        local_2c = iVar5;
      } while (iVar2 < 0x10);
    }
    lVar3 = DisplayInterface::colorYellow;
    if (this->buildTeam != -1) {
      lVar3 = DisplayInterface::colorGreen;
    }
    DrawKeyItem(this,0x1a4,iVar5,this[1]._padding_ + 9,"Default",lVar3,DisplayInterface::colorBlack)
    ;
    if (command_controls.mode_select[9] != '\0') {
      this->buildTeam = -1;
      this->teamMode = TEAM_NORMAL;
      this->menuMode = MENU_NONE;
    }
    lVar3 = DisplayInterface::colorYellow;
    if (this->buildTeam != 0) {
      lVar3 = DisplayInterface::colorGreen;
    }
    DrawKeyItem(this,0x1a4,iVar5 + 0xb,this[1]._padding_,"Neutral",lVar3,
                DisplayInterface::colorBlack);
    if (command_controls.mode_select[0] != '\0') {
      this->buildTeam = 0;
      this->teamMode = TEAM_NORMAL;
      this->menuMode = MENU_NONE;
    }
    if (this->teamMode == TEAM_NORMAL) {
      DrawKeyItem(this,0x1a4,iVar5 + 0x1b,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                  DisplayInterface::colorBlack);
      if (command_controls.menu_back != '\0') {
        this->menuMode = MENU_NONE;
      }
    }
    else {
      DrawKeyItem(this,0x1a4,iVar5 + 0x1b,this[1]._padding_,"Back",DisplayInterface::colorWhite,
                  DisplayInterface::colorBlack);
      if (command_controls.menu_back != '\0') {
        this->teamMode = TEAM_NORMAL;
      }
    }
  }
  else {
    iVar2 = this->buildTeam;
    if (iVar2 < 1) {
      local_10 = "Default";
      local_c = "Neutral";
      Graphic_Text(DisplayInterface::currentBuffer,0x1a4,0x1a,&local_34,&local_30,(&local_c)[iVar2],
                   DisplayInterface::textFont,DisplayInterface::colorWhite,
                   DisplayInterface::colorBlack,0,0,0);
    }
    else {
      sprintf(local_18,"Team %d",iVar2);
      Graphic_Text(DisplayInterface::currentBuffer,0x1a4,0x1a,&local_34,&local_30,local_18,
                   DisplayInterface::textFont,DisplayInterface::colorWhite,
                   DisplayInterface::colorBlack,0,0,0);
    }
  }
  return;
}
