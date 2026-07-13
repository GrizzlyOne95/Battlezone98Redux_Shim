/*
 * Entry: 00478df5
 * Name: WindowProc
 * Namespace: Global
 * Signature: long WindowProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

long __cdecl WindowProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  int iVar1;
  UINT UVar2;
  LRESULT LVar3;
  void *pvVar4;
  ulong uVar5;
  HANDLE pvVar6;
  undefined4 uStackY_74;
  char *pcVar7;
  DWORD dwPriorityClass;
  UINT local_4c;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 == 0x104) {
    if (param_3 == 0xd) {
      if (useD3D != 0) {
        UseDDraw = (int)(UseDDraw == 0);
        (*Device.VideoMode.ChangeMode)(&Device,ResolutionMode);
        goto LAB_00478e83;
      }
    }
    else {
      if (param_3 == 0x1b) {
        return 0;
      }
      if (param_3 == 0x20) {
        return 0;
      }
    }
LAB_00478e32:
    if (param_2 == 0x104) {
      Trace("WM_SYSKEYDOWN: hWnd(%x) wParam(%x) lParam(%x)\n");
      goto LAB_00478f26;
    }
    if (param_2 == 0x105) {
      pcVar7 = "WM_SYSKEYUP: hWnd(%x) wParam(%x) lParam(%x)\n";
    }
    else {
      if (param_2 != 0x106) goto LAB_00478f26;
      pcVar7 = "WM_SYSCHAR: hWnd(%x) wParam(%x) lParam(%x)\n";
    }
LAB_00478eb0:
    Trace(pcVar7);
LAB_00478eb8:
    if (runningSS == 6) {
      iVar1 = (*pShellWindowProc)();
      return iVar1;
    }
    if (param_2 == 0xff) {
      uStackY_74 = 0x478fa5;
      GetRawInputData((HRAWINPUT)param_4,0x10000003,(LPVOID)0x0,&local_4c,0x10);
      iVar1 = -local_4c;
      *(undefined4 *)((int)&local_48 + iVar1 + -0x18) = 0x10;
      *(UINT **)((int)&local_48 + iVar1 + -0x1c) = &local_4c;
      *(int *)((int)&local_48 + iVar1 + -0x20) = (int)&local_48 + iVar1 + -0x14;
      *(undefined4 *)(&stack0xffffff94 + iVar1) = 0x10000003;
      *(long *)(&stack0xffffff90 + iVar1) = param_4;
      *(undefined4 *)((int)&uStackY_74 + iVar1) = 0x478fbd;
      UVar2 = GetRawInputData(*(HRAWINPUT *)(&stack0xffffff90 + iVar1),
                              *(UINT *)(&stack0xffffff94 + iVar1),
                              *(LPVOID *)((int)&local_48 + iVar1 + -0x20),
                              *(PUINT *)((int)&local_48 + iVar1 + -0x1c),
                              *(UINT *)((int)&local_48 + iVar1 + -0x18));
      if (UVar2 != local_4c) {
        *(char **)((int)&local_48 + iVar1 + -0x18) =
             "GetRawInputData does not return correct size !\n";
        *(undefined4 *)((int)&local_48 + iVar1 + -0x1c) = 0x478fcd;
        OutputDebugStringA(*(LPCSTR *)((int)&local_48 + iVar1 + -0x18));
      }
      if (*(int *)((int)&local_48 + iVar1 + -0x14) != 0) {
        return 0;
      }
      if (ResolutionMode == 0) {
        return 0;
      }
      *(int *)((int)&local_48 + iVar1 + -0x18) = (int)&local_48 + iVar1 + -4;
      *(undefined4 *)((int)&local_48 + iVar1 + -0x1c) = 0x478fef;
      ProcessMouseRawInput(*(tagRAWMOUSE **)((int)&local_48 + iVar1 + -0x18));
      return 0;
    }
    if ((0xff < param_2) && (param_2 < 0x10a)) {
      if (ResolutionMode != 0) {
        if (ScreenMode != SCREENMODE_PAUSE) {
          pvVar4 = TextInput_IsActive();
          if (pvVar4 == (void *)0x0) {
            ProcessKeyboardMessages(param_2,param_3,param_4);
            return 0;
          }
          uVar5 = TextInput_ProcessInput(pvVar4,param_2,param_3,param_4);
          if (uVar5 == 0) {
            return 0;
          }
          if (uVar5 != 2) {
            return 0;
          }
          TextInput_AllowInput(pvVar4,0);
          return 0;
        }
        if (param_2 != 0x100) {
          return 0;
        }
        if (param_3 != 0x13) {
          return 0;
        }
        PauseKeyToggle();
        return 0;
      }
      if (param_3 == 0x20) {
        iVar1 = check_load_voice();
        if (iVar1 != 0) {
          stop_load_voice();
          goto LAB_0047902a;
        }
      }
      else {
LAB_0047902a:
        if ((param_3 == 0x1b) && (nDemoState != 0)) {
          nDemoState = 0;
        }
      }
      if ((((ScreenMode == SCREENMODE_MOVIE) && (param_2 == 0x100)) && (param_3 == 0x1b)) &&
         (iVar1 = movie_is_playing(), iVar1 != 0)) {
        movie_close();
        ScreenMode = SCREENMODE_SIM;
      }
      goto LAB_00479073;
    }
    if ((0x1ff < param_2) && (param_2 < 0x20f)) {
      if (ResolutionMode != 0) {
        if (UseRawInput != 0) {
          return 0;
        }
        ProcessMouseMessages(param_2,param_3,param_4);
        return 0;
      }
      if ((param_2 == 0x201) && (nDemoState != 0)) {
        nDemoState = 0;
      }
      goto LAB_00479073;
    }
    if (param_2 < 0x11) {
      if (param_2 == 0x10) {
        runningSS = 10;
        return 0;
      }
      if (param_2 == 1) {
        DEBUG_setWindowHandle(param_1);
        shell_hwnd = param_1;
        return 0;
      }
      if (param_2 == 2) {
        runningSS = 2;
        return 0;
      }
      if (param_2 == 5) {
        if (bIgnoreWM_SIZE == 0) {
          GetClientRect((HWND)param_1,(LPRECT)&Device.winRect);
          Device.Client_Width = Device.winRect.right - Device.winRect.left;
          Device.Client_Height = Device.winRect.bottom - Device.winRect.top;
          GetWindowRect((HWND)param_1,(LPRECT)&Device.winRect);
          Device.winRect.right = Device.winRect.right - Device.winRect.left;
          Device.winRect.bottom = Device.winRect.bottom - Device.winRect.top;
          if (param_3 != 0) {
            return 0;
          }
          if (Device.VideoMode.Restore == (_func___cdecl_void_void_ptr *)0x0) {
            return 0;
          }
          (*Device.VideoMode.Restore)(&Device);
          return 0;
        }
        param_2 = 5;
      }
      else if (param_2 == 6) {
        if (ResolutionMode == 0) {
          return 0;
        }
        param_2 = 6;
      }
      else {
        if (param_2 == 7) {
          ClearKeyboardState();
          return 0;
        }
        if (param_2 == 0xf) {
          if ((noPaint == 0) && (ResolutionMode != 0)) {
            BeginPaint((HWND)param_1,&local_48);
            if ((WeAreActive != 0) &&
               ((ScreenMode &
                (SCREENMODE_MOVIE|SCREENMODE_MENU|SCREENMODE_NOTEPAD|SCREENMODE_MAP|SCREENMODE_PAUSE
                )) != 0)) {
              (*Device.Refresh.Blit)(&Device);
            }
            EndPaint((HWND)param_1,&local_48);
            return 0;
          }
          param_2 = 0xf;
        }
      }
      goto LAB_00479073;
    }
  }
  else {
LAB_00478e83:
    if (0x102 < param_2) goto LAB_00478e32;
    if (param_2 == 0x102) {
      pcVar7 = "WM_CHAR: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_00478eb0;
    }
    if (param_2 == 6) {
      pcVar7 = "WM_ACTIVATE: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_00478eb0;
    }
    if (param_2 == 7) {
      pcVar7 = "WM_SETFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_00478eb0;
    }
    if (param_2 == 8) {
      pcVar7 = "WM_KILLFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_00478eb0;
    }
    if (param_2 == 0x1c) {
      pcVar7 = "WM_ACTIVATEAPP: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_00478eb0;
    }
LAB_00478f26:
    if (param_2 != 0x432) goto LAB_00478eb8;
    runningSS = 5;
  }
  if (param_2 == 0x1c) {
    if (param_3 == 0) {
      if (WeAreActive == 0) {
        return 0;
      }
      WeAreActive = 0;
      prev_focus = (HWND__ *)GetFocus();
      if (UseDDraw != 0) {
        ShowWindow((HWND)param_1,6);
      }
      if (ResolutionMode == 0) {
        return 0;
      }
      iVar1 = Net_IsNetGame();
      if (iVar1 == 0) {
        PauseAudio();
        Pause();
      }
      dwPriorityClass = 0x20;
      pvVar6 = GetCurrentProcess();
      SetPriorityClass(pvVar6,dwPriorityClass);
      iVar1 = 0;
      pvVar6 = GetCurrentThread();
      SetThreadPriority(pvVar6,iVar1);
      if (ScreenMode != SCREENMODE_SIM) {
        return 0;
      }
      DisableForceFeedback();
      UnlockMouse();
      return 0;
    }
    if (WeAreActive != 0) {
      return 0;
    }
    WeAreActive = 1;
    if (UseDDraw != 0) {
      ShowWindow((HWND)param_1,9);
    }
    if (ResolutionMode != 0) {
      SetFocus((HWND)param_1);
      iVar1 = Net_IsNetGame();
      if (iVar1 == 0) {
        UnPauseAudio();
        Resume();
      }
      if (ScreenMode == SCREENMODE_MENU) {
        Render_Next_Frame(&View_Record.MainCam);
        DrawMenuContents();
      }
      ClearKeyboardState();
      if (ScreenMode != SCREENMODE_SIM) {
        return 0;
      }
      EnableForceFeedback();
      LockMouse();
      return 0;
    }
    SetFocus((HWND)prev_focus);
    return 0;
  }
  if (param_2 == 0x20) {
    set_cursor(0);
    return 1;
  }
  if (param_2 == 0x30f) {
    return 1;
  }
  if (param_2 == 0x311) {
    if ((HWND__ *)param_3 == Device.hwndApp) {
      return 0;
    }
    return 1;
  }
  if (param_2 == 0x3b9) {
    movie_check(param_3,param_4);
    ScreenMode = SCREENMODE_SIM;
    return 0;
  }
LAB_00479073:
  LVar3 = DefWindowProcA((HWND)param_1,param_2,param_3,param_4);
  return LVar3;
}
