
undefined4 * __thiscall FUN_00584eb0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = Ordnance::vftable;
  FUN_00430590();
  param_1[3] = param_3;
  param_1[5] = param_2;
  FUN_00423890();
  param_1[4] = 0;
  *(undefined2 *)(param_1 + 0x1f) = 0;
  *(undefined2 *)((int)param_1 + 0x7e) = 0;
  param_1[0x20] = 1;
  return param_1;
}

