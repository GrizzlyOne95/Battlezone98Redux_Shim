
undefined4 * __fastcall FUN_004e7320(undefined4 *param_1)

{
  FUN_004e53a0();
  *param_1 = GoPoints::vftable;
  param_1[2] = 6;
  param_1[3] = 6;
  param_1[0x53] = 0;
  *(undefined1 *)((int)param_1 + 0x13e) = 1;
  return param_1;
}

