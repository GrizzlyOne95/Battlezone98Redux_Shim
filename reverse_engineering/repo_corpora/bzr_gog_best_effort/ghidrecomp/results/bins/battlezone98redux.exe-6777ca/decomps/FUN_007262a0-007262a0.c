
undefined4 * __thiscall FUN_007262a0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  FUN_0071e250(param_2 + 2);
  return param_1;
}

