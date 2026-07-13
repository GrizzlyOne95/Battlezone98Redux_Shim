
undefined4 * __thiscall FUN_007270d0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  uVar1 = param_2[3];
  param_1[2] = param_2[2];
  param_1[3] = uVar1;
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  FUN_00705510(param_2 + 6);
  return param_1;
}

