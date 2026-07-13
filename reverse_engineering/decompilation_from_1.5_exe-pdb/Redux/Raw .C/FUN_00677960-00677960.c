
undefined4 * __thiscall FUN_00677960(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  FUN_00667cf0(param_2 + 4);
  return param_1;
}

