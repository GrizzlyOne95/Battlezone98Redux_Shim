
undefined4 * __thiscall FUN_00721260(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  *param_2 = 0;
  param_2[1] = 0;
  return param_1;
}

