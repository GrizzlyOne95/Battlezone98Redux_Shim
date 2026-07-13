/*
 * Entry: 004bd66c
 * Name: ProcessKeyboardMessages
 * Namespace: Global
 * Signature: void ProcessKeyboardMessages(uint param_1, uint param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessKeyboardMessages(uint param_1,uint param_2,long param_3)

{
  BOOL BVar1;
  char *pcVar2;
  tagMSG local_20;
  
  local_20.hwnd = (HWND)0x0;
  local_20.message = param_1;
  local_20.wParam = param_2;
  local_20.lParam = param_3;
  do {
    if (param_1 == 0x100) {
LAB_004bd6c1:
      if (param_2 == 0x14) {
        if (((param_3 & 0xf0000U) == 0) || ((param_3 & 0x40000000U) != 0)) goto LAB_004bd6fb;
        keybd_event('\x14','\0',3,0);
        keybd_event('\x14','\0',1,0);
      }
      StoreGameKey(param_2,param_3);
      UpdateKeyboardState(param_2,param_3,1);
    }
    else if (param_1 == 0x101) {
LAB_004bd6a6:
      if ((param_2 != 0x14) || ((param_3 & 0xf0000U) != 0)) {
        UpdateKeyboardState(param_2,param_3,0);
      }
    }
    else {
      if (param_1 == 0x104) goto LAB_004bd6c1;
      if (param_1 == 0x105) goto LAB_004bd6a6;
    }
LAB_004bd6fb:
    if (((param_1 == 0x104) && (param_2 != 0x1b)) && (param_2 != 0x20)) {
      DefWindowProcA(local_20.hwnd,local_20.message,local_20.wParam,local_20.lParam);
    }
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x100,0x109,1);
    if (BVar1 == 0) {
      return;
    }
    TranslateMessage(&local_20);
    param_3 = local_20.lParam;
    param_2 = local_20.wParam;
    param_1 = local_20.message;
    if (local_20.message == 6) {
      pcVar2 = "WM_ACTIVATE: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 7) {
      pcVar2 = "WM_SETFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 8) {
      pcVar2 = "WM_KILLFOCUS: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 0x1c) {
      pcVar2 = "WM_ACTIVATEAPP: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 0x104) {
      pcVar2 = "WM_SYSKEYDOWN: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 0x105) {
      pcVar2 = "WM_SYSKEYUP: hWnd(%x) wParam(%x) lParam(%x)\n";
      goto LAB_004bd7ca;
    }
    if (local_20.message == 0x106) {
      pcVar2 = "WM_SYSCHAR: hWnd(%x) wParam(%x) lParam(%x)\n";
LAB_004bd7ca:
      Trace(pcVar2);
    }
  } while( true );
}
