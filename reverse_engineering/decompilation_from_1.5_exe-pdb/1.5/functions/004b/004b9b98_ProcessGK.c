/*
 * Entry: 004b9b98
 * Name: ProcessGK
 * Namespace: Global
 * Signature: void ProcessGK(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessGK(int param_1)

{
  tagENTITY *ptVar1;
  int iVar2;
  GKCommandKey GVar3;
  
  ptVar1 = get_user_entity();
  iVar2 = Net_IsNetGame();
  if ((iVar2 != 0) && (ptVar1 == (tagENTITY *)0x0)) {
    if ((param_1 != 0x17) && (param_1 != 0x18)) {
      return;
    }
    SetRunning(2);
    return;
  }
  if (param_1 < 0x1a) {
    if (param_1 == 0x19) {
      Mono_Toggle();
      LastKey = param_1;
      return;
    }
    if (param_1 < 0x10) {
      if (param_1 == 0xf) {
        if (UseDDraw != 0) {
          LastKey = param_1;
          return;
        }
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        PromptSaveMission();
        LastKey = param_1;
        return;
      }
      if (param_1 == 0) {
        LastKey = param_1;
        return;
      }
      if (param_1 == 10) {
        if (useD3D != 0) {
          LastKey = param_1;
          return;
        }
        Graphic_Buffer_Save(&Device);
        LastKey = param_1;
        return;
      }
      if (param_1 == 0xb) {
        do_escape();
        LastKey = param_1;
        return;
      }
      if (param_1 == 0xe) {
        if (UseDDraw != 0) {
          LastKey = param_1;
          return;
        }
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        PromptLoadGame();
        LastKey = param_1;
        return;
      }
    }
    else {
      if (param_1 == 0x15) {
        hudFlags = (uint)(hudFlags == 0);
        LastKey = param_1;
        return;
      }
      if (param_1 == 0x16) {
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        PauseKeyToggle();
        LastKey = param_1;
        return;
      }
      if (param_1 == 0x17) {
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        iVar2 = 0;
LAB_004b9c97:
        SetRunning(iVar2);
        LastKey = param_1;
        return;
      }
      if (param_1 == 0x18) {
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        iVar2 = 1;
        goto LAB_004b9c97;
      }
    }
  }
  else if (param_1 < 0x1f) {
    if (param_1 == 0x1e) {
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x1a) {
      Mono_Next();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x1b) {
      Mono_Prev();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x1c) {
      Mono_PageUp();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x1d) {
      Mono_PageDown();
      LastKey = param_1;
      return;
    }
  }
  else {
    if (param_1 == 0x1f) {
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x23) {
      Toggle_Framerate();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x24) {
      Network_ToggleDisplay();
      LastKey = param_1;
      return;
    }
  }
  iVar2 = is_user_dead();
  if (iVar2 != 0) {
    LastKey = param_1;
    return;
  }
  GVar3 = param_1;
  if (param_1 < 0x22) {
    if (param_1 == 0x21) {
      IncVar();
      LastKey = param_1;
      return;
    }
    if (param_1 < 0x13) {
      if (param_1 != 0x12) {
        if (param_1 < 1) {
          LastKey = param_1;
          return;
        }
        if (param_1 < 6) {
          iVar2 = isCineractive();
          if (iVar2 != 0) {
            LastKey = param_1;
            return;
          }
          if (ptVar1 == (tagENTITY *)0x0) {
            if ((int)View_Record.Current_View < 10) {
              LastKey = param_1;
              return;
            }
            ptVar1 = (tagENTITY *)0x0;
            GVar3 = GK_FREE_EYE_VIEW;
          }
        }
        else if (9 < param_1) {
          if (param_1 == 0x10) {
            iVar2 = Net_IsNetGame();
            if (iVar2 == 0) {
              LastKey = param_1;
              return;
            }
            Chat_Toggle();
            LastKey = param_1;
            return;
          }
          if (param_1 != 0x11) {
            LastKey = param_1;
            return;
          }
          iVar2 = Net_IsNetGame();
          if (iVar2 == 0) {
            LastKey = param_1;
            return;
          }
          Chat_InputMessage(0);
          LastKey = param_1;
          return;
        }
        goto LAB_004b9df1;
      }
      iVar2 = Net_IsNetGame();
      if (iVar2 == 0) {
        LastKey = param_1;
        return;
      }
      iVar2 = 1;
    }
    else {
      if (param_1 != 0x13) {
        if (param_1 == 0x14) {
          iVar2 = Net_IsNetGame();
          if (iVar2 == 0) {
            LastKey = param_1;
            return;
          }
          Scores_Toggle();
          LastKey = param_1;
          return;
        }
        if (param_1 != 0x20) {
          LastKey = param_1;
          return;
        }
        AdvanceVar();
        LastKey = param_1;
        return;
      }
      iVar2 = Net_IsNetGame();
      if (iVar2 == 0) {
        LastKey = param_1;
        return;
      }
      iVar2 = 0;
    }
    ALLIE_InputMessage(iVar2);
  }
  else {
    if (param_1 == 0x22) {
      DecVar();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x26) {
      InfoDisplay_Info();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x27) {
      InfoDisplay_Objectives();
      LastKey = param_1;
      return;
    }
    if (param_1 == 0x28) {
      RepeatAudioMessage();
      LastKey = param_1;
      return;
    }
    if (param_1 != 0x29) {
      if (param_1 == 0x2a) {
        if (TerrainEdit == 0) {
          LastKey = param_1;
          return;
        }
        iVar2 = Net_IsNetGame();
        if (iVar2 != 0) {
          LastKey = param_1;
          return;
        }
        UserProfilePtr->playOption = UserProfilePtr->playOption ^ 1;
        LastKey = param_1;
        return;
      }
      if (param_1 != 0x2c) {
        LastKey = param_1;
        return;
      }
      if (useD3D != 0) {
        LastKey = param_1;
        return;
      }
      (UserProfilePtr->graphicDetail).lineskip = (UserProfilePtr->graphicDetail).lineskip == '\0';
      SaveUserProfile();
      LastKey = param_1;
      return;
    }
LAB_004b9df1:
    Set_View(ptVar1,GVar3);
  }
  LastKey = param_1;
  return;
}
