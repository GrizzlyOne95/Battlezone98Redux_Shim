
undefined4 FUN_00434640(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  while( true ) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,0);
    if (BVar1 == 0) {
      return 1;
    }
    BVar1 = GetMessageA(&local_20,(HWND)0x0,0,0);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return 0;
}

