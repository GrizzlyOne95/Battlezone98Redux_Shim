
void FUN_00434600(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  while( true ) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return;
}

