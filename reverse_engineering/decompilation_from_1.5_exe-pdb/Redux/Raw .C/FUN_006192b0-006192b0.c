
void FUN_006192b0(int param_1)

{
  BOOL BVar1;
  tagMSG local_24;
  int local_8;
  
  local_8 = FUN_00616e40(param_1);
  while ((local_8 == 0 && (BVar1 = PeekMessageA(&local_24,(HWND)0x0,0,0,1), BVar1 != 0))) {
    if ((local_24.hwnd == (HWND)0x0) || (local_24.message != 0x12)) {
      TranslateMessage(&local_24);
      DispatchMessageA(&local_24);
    }
    else {
      *(undefined4 *)(param_1 + 0x6c) = 1;
      DAT_009183d8 = local_24.wParam;
    }
  }
  if ((DAT_00920ed0 != 0) && (DAT_00920ecc != 0)) {
    FUN_006834b0();
  }
  return;
}

