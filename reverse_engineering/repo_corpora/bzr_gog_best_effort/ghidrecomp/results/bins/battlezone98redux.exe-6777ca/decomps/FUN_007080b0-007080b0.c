
undefined4 * __thiscall FUN_007080b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  uVar1 = param_3[1];
  param_1[2] = *param_3;
  param_1[3] = uVar1;
  return param_1;
}

