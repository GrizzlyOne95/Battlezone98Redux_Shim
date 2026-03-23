
void FUN_00618bc0(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  while( true ) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  if ((DAT_00920ed0 != 0) && (DAT_00920ecc != 0)) {
    FUN_006834b0();
  }
  return;
}

