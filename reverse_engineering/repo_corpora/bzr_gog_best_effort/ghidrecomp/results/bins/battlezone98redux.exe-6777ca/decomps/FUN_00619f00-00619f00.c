
void FUN_00619f00(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x100,0x109,1);
  if (BVar1 != 0) {
    FUN_00619be0(local_20.message,local_20.wParam,local_20.lParam);
  }
  return;
}

