
undefined2 * __thiscall
FUN_008417a0(undefined4 param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_2 + 10) = 7;
  *(undefined4 *)(param_2 + 8) = 0;
  *param_2 = 0;
  FID_conflict_assign(param_1,param_3,param_4);
  return param_2;
}

