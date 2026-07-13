/*
 * Entry: 0050436b
 * Name: Device_Set_Graphic_Mode
 * Namespace: Global
 * Signature: int Device_Set_Graphic_Mode(VIDEO_DEVICE * param_1, int param_2, WINDOW_MODE param_3, REFRESH_MODE param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Device_Set_Graphic_Mode
          (VIDEO_DEVICE *param_1,int param_2,WINDOW_MODE param_3,REFRESH_MODE param_4,int param_5)

{
  LPRECT lpRect;
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *in_EAX;
  HDC hdc;
  int in_ECX;
  int iVar4;
  VIDEO_MODE_CLASS *pVVar5;
  VIDEO_MODE *pVVar6;
  DWORD dwStyle;
  HWND pHVar7;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  LONG local_18;
  int local_10;
  int local_c;
  
  uVar1 = *(undefined4 *)(&DAT_0062da78 + in_ECX * 0x20);
  uVar2 = *(undefined4 *)(&DAT_0062da7c + in_ECX * 0x20);
  in_EAX[0xfa] = gdiRefreshMode.id;
  in_EAX[0xfb] = gdiRefreshMode.Blit;
  in_EAX[0xfc] = gdiRefreshMode.BlitFill;
  in_EAX[0xfd] = gdiRefreshMode.CopyBackBuffer;
  pVVar5 = &gdiVideoMode;
  pVVar6 = in_EAX + 0xed;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pVVar6 = pVVar5->id;
    pVVar5 = (VIDEO_MODE_CLASS *)&pVVar5->windowMode;
    pVVar6 = pVVar6 + 1;
  }
  dwStyle = in_EAX[0xef];
  in_EAX[0xee] = param_1;
  lpRect = (LPRECT)(in_EAX + 0x24);
  *in_EAX = uVar1;
  in_EAX[1] = uVar2;
  lpRect->left = 0;
  in_EAX[0x25] = 0;
  in_EAX[0x26] = uVar1;
  in_EAX[0x27] = uVar2;
  in_EAX[0xe] = uVar1;
  in_EAX[0xf] = uVar2;
  AdjustWindowRect(lpRect,dwStyle,param_2);
  in_EAX[0x26] = in_EAX[0x26] - lpRect->left;
  in_EAX[0x27] = in_EAX[0x27] - in_EAX[0x25];
  local_10 = in_EAX[0x10];
  iVar4 = in_EAX[0x11];
  iVar3 = in_EAX[0x27];
  lpRect->left = local_10 - in_EAX[0x26] >> 1;
  in_EAX[0x25] = iVar4 - iVar3 >> 1;
  if (param_1 == (VIDEO_DEVICE *)0x0) {
    local_c = in_EAX[0x11];
    local_18 = 0;
  }
  else {
    local_18 = lpRect->left;
    local_10 = in_EAX[0x26];
    local_c = in_EAX[0x27];
  }
  pHVar7 = (HWND)in_EAX[0x22];
  if (pHVar7 == (HWND)0x0) {
    lpParam = (LPVOID)0x0;
    hInstance = (HINSTANCE)in_EAX[0x23];
    hMenu = (HMENU)0x0;
    pHVar7 = (HWND)0x0;
    if (param_1 == (VIDEO_DEVICE *)0x0) {
      local_c = GetSystemMetrics(1);
      local_10 = GetSystemMetrics(0);
      local_18 = 0;
      dwStyle = 0x90080000;
    }
    pHVar7 = CreateWindowExA(0,(LPCSTR)(in_EAX + 0x12),(LPCSTR)(in_EAX + 0x12),dwStyle,local_18,0,
                             local_10,local_c,pHVar7,hMenu,hInstance,lpParam);
    if (pHVar7 == (HWND)0x0) {
      in_EAX[0x2c] = 5;
      return 0;
    }
    in_EAX[0x22] = pHVar7;
    if (in_EAX[0xed] == 2) {
      if (in_EAX[0xee] == 0) {
        SetMenu(pHVar7,(HMENU)0x0);
        ShowWindow(pHVar7,10);
        UpdateWindow(pHVar7);
      }
    }
    else if ((in_EAX[0xed] == 0) && (in_EAX[0xee] == 0)) {
      UpdateWindow(pHVar7);
      SetFocus(pHVar7);
    }
  }
  iVar4 = (*(code *)in_EAX[0xf0])();
  if (iVar4 == 0) {
    return 0;
  }
  if ((in_EAX[0xed] == 2) || (in_EAX[0xee] == 1)) {
    ShowWindow((HWND)in_EAX[0x22],5);
  }
  hdc = GetDC(pHVar7);
  iVar4 = GetDeviceCaps(hdc,0x18);
  ReleaseDC(pHVar7,hdc);
  if ((iVar4 != -1) && (in_EAX[0xed] == 2)) {
    MessageBoxA(pHVar7,"Your system must be in 16-bit color mode to play BattleZone in a window.",
                "BattleZone",0x10);
    LastInputs();
                    /* WARNING: Subroutine does not return */
    exit(0x6c);
  }
  return 1;
}
