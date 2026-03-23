
bool FUN_00435030(LONG *param_1)

{
  BOOL BVar1;
  tagPOINT local_14 [2];
  
  BVar1 = ScreenToClient((HWND)*DAT_02cecefc,local_14);
  if (param_1 != (LONG *)0x0) {
    *param_1 = local_14[0].x;
    param_1[1] = local_14[0].y;
  }
  return param_1 != (LONG *)0x0 && BVar1 != 0;
}

