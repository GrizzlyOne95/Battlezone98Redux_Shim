
undefined4 * __thiscall FUN_004e7370(undefined4 *param_1,undefined4 param_2)

{
  FUN_004e54c0(param_2,0,1);
  *param_1 = GoPoints::vftable;
  param_1[2] = 6;
  param_1[3] = 6;
  param_1[0x53] = 0;
  *(undefined1 *)((int)param_1 + 0x13e) = 1;
  return param_1;
}

