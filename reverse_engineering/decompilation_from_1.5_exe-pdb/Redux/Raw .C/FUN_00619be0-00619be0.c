
void FUN_00619be0(uint param_1,WPARAM param_2,uint param_3)

{
  BOOL BVar1;
  tagMSG local_38;
  WPARAM local_1c;
  int local_18;
  uint local_14;
  HWND local_10;
  uint local_c;
  uint local_8;
  
  local_18 = 0;
  local_38.hwnd = (HWND)0x0;
  local_38.message = param_1;
  local_38.wParam = param_2;
  local_38.lParam = param_3;
  local_8 = 0;
  do {
    local_14 = param_1 - 0x100;
    if (local_14 < 6) {
      switch(local_14) {
      default:
        if (param_2 == 0x14) {
          if (((param_3 & 0xf0000) == 0) || ((param_3 & 0x40000000) != 0)) break;
          keybd_event('\x14','\0',3,0);
          keybd_event('\x14','\0',1,0);
        }
        if ((param_3 & 0x40000000) == 0) {
          FUN_00434b00(param_2);
        }
        local_8 = (int)param_3 >> 0x10 & 0xff;
        if ((local_8 != 0) && ((param_3 >> 0x10 & 0x100) != 0)) {
          local_8 = FUN_00434bd0(local_8);
        }
        FUN_00434bf0(local_8,1);
        break;
      case 1:
      case 5:
        if ((param_2 != 0x14) || ((param_3 & 0xf0000) != 0)) {
          local_8 = (int)param_3 >> 0x10 & 0xff;
          if ((local_8 != 0) && ((param_3 >> 0x10 & 0x100) != 0)) {
            local_8 = FUN_00434bd0(local_8);
          }
          FUN_00434bf0(local_8,0);
        }
        break;
      case 2:
      case 3:
        break;
      }
    }
    if ((((0x103 < param_1) && (param_1 == 0x104)) && (local_1c = param_2, param_2 != 0x1b)) &&
       (param_2 != 0x20)) {
      CallWindowProcA(DAT_00918400,local_38.hwnd,local_38.message,local_38.wParam,local_38.lParam);
    }
    BVar1 = PeekMessageA(&local_38,(HWND)0x0,0x100,0x109,1);
    if (BVar1 == 0) {
      local_18 = 1;
    }
    else {
      TranslateMessage(&local_38);
      param_1 = local_38.message;
      param_2 = local_38.wParam;
      param_3 = local_38.lParam;
    }
    if (local_18 == 0) {
      local_10 = local_38.hwnd;
      local_c = param_1;
      if (param_1 < 0x1d) {
        if (param_1 == 0x1c) {
          FUN_007d6a70("WM_ACTIVATEAPP: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,
                       param_3);
        }
        else if (param_1 == 6) {
          FUN_007d6a70("WM_ACTIVATE: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,param_3
                      );
        }
        else if (param_1 == 7) {
          FUN_007d6a70("WM_SETFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,param_3
                      );
        }
        else if (param_1 == 8) {
          FUN_007d6a70("WM_KILLFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,
                       param_3);
        }
      }
      else if (param_1 == 0x104) {
        FUN_007d6a70("WM_SYSKEYDOWN: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,param_3
                    );
      }
      else if (param_1 == 0x105) {
        FUN_007d6a70("WM_SYSKEYUP: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,param_3);
      }
      else if (param_1 == 0x106) {
        FUN_007d6a70("WM_SYSCHAR: hWnd(%x) wParam(%x) lParam(%x)\n",local_38.hwnd,param_2,param_3);
      }
    }
    if (local_18 != 0) {
      return;
    }
  } while( true );
}

