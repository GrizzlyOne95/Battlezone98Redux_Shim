
undefined4 * __thiscall FUN_007261e0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  FUN_00726d20(param_2 + 2);
  return param_1;
}

