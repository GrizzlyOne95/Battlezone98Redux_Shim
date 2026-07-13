
bool FUN_00434fd0(LONG *param_1)

{
  BOOL BVar1;
  tagPOINT local_14 [2];
  
  local_14[0].x = *param_1;
  local_14[0].y = param_1[1];
  BVar1 = ClientToScreen((HWND)*DAT_02cecefc,local_14);
  *param_1 = local_14[0].x;
  param_1[1] = local_14[0].y;
  return BVar1 != 0;
}

