/*
 * Entry: 004b9750
 * Name: test_cheat_codes
 * Namespace: Global
 * Signature: void test_cheat_codes(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl test_cheat_codes(ushort param_1)

{
  int iVar1;
  float10 extraout_ST0;
  float10 extraout_ST1;
  
  iVar1 = add_to_cheat_buf(param_1);
  if (iVar1 != 0) {
    iVar1 = Net_IsNetGame();
    if (iVar1 == 0) {
      iVar1 = test_for_cheat("bzfree");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 2;
        if ((UserProfilePtr->playOption & 2) == 0) {
          ColorFade_SetFade((float)extraout_ST0,(float)extraout_ST1,0x66,0x66,0x66);
        }
        else {
          ColorFade_SetFade((float)extraout_ST0,(float)extraout_ST1,0xff,0xff,0xff);
          DoAudioNew("suck.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
        }
      }
      iVar1 = test_for_cheat("bztnt");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 4;
        if ((UserProfilePtr->playOption & 4) == 0) {
          ColorFade_SetFade(1.0,5.0,0,0x33,0x66);
        }
        else {
          ColorFade_SetFade(1.0,5.0,0,0x80,0xff);
          DoAudioNew("weapon.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
        }
      }
      iVar1 = test_for_cheat("bzbody");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 8;
        if ((UserProfilePtr->playOption & 8) == 0) {
          ColorFade_SetFade(1.0,5.0,0,0x66,0);
        }
        else {
          ColorFade_SetFade(1.0,5.0,0,0xff,0);
          DoAudioNew("repair.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
        }
      }
      iVar1 = test_for_cheat("bzview");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x100;
        if ((UserProfilePtr->playOption & 0x100U) == 0) {
          ColorFade_SetFade(1.0,5.0,0x66,0x66,0);
        }
        else {
          ColorFade_SetFade(1.0,5.0,0xff,0xff,0);
          DoAudioNew("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
        }
      }
      iVar1 = test_for_cheat("bzradar");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x200;
        if ((UserProfilePtr->playOption & 0x200U) == 0) {
          ColorFade_SetFade(1.0,5.0,0x66,0,0x66);
        }
        else {
          ColorFade_SetFade(1.0,5.0,0xff,0,0xff);
          DoAudioNew("ping.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
        }
      }
      iVar1 = test_for_cheat("god");
      if (iVar1 != 0) {
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 4;
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 8;
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x200;
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x100;
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 2;
        ColorFade_SetFade(1.0,0.5,0xf4,0xf4,0xf4);
        DoAudioNew("weapon.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
      }
      iVar1 = test_for_cheat("drawcoll");
      if (iVar1 != 0) {
        toggle_show_collision();
      }
      iVar1 = test_for_cheat("drawguns");
      if (iVar1 != 0) {
        toggle_show_hardpoints();
      }
    }
    iVar1 = test_for_cheat("loggit");
    if (iVar1 != 0) {
      network_loggit = (int)(network_loggit == 0);
    }
    iVar1 = test_for_cheat("time");
    if (iVar1 != 0) {
      Toggle_NetworkTimer();
    }
    iVar1 = test_for_cheat("waves");
    if (iVar1 != 0) {
      waveEnable = (int)(waveEnable == 0);
    }
    iVar1 = test_for_cheat("level");
    if (iVar1 != 0) {
      UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x10;
      if ((UserProfilePtr->playOption & 0x10) == 0) {
        ColorFade_SetFade(1.0,5.0,0,0,0);
      }
      else {
        ColorFade_SetFade(1.0,5.0,0xff,0xd7,0);
        DoAudioNew("ping.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
      }
    }
    iVar1 = test_for_cheat("flip");
    if (iVar1 != 0) {
      UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x40;
      if ((UserProfilePtr->playOption & 0x40) == 0) {
        ColorFade_SetFade(1.0,5.0,0,0,0);
      }
      else {
        ColorFade_SetFade(1.0,5.0,0xff,0xd7,0);
        DoAudioNew("ping.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
      }
    }
    iVar1 = test_for_cheat("aim");
    if (iVar1 != 0) {
      UserProfilePtr->playOption = UserProfilePtr->playOption ^ 0x20;
      if ((UserProfilePtr->playOption & 0x20) == 0) {
        ColorFade_SetFade(1.0,5.0,0,0,0);
      }
      else {
        ColorFade_SetFade(1.0,5.0,0xff,0xd7,0);
        DoAudioNew("ping.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0);
      }
    }
  }
  return;
}
