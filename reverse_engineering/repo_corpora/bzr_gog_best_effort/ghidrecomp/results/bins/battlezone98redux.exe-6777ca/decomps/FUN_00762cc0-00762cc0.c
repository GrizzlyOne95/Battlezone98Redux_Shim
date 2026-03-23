
undefined4 * __thiscall FUN_00762cc0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  *param_1 = *param_2;
  uVar1 = param_2[3];
  param_1[2] = param_2[2];
  param_1[3] = uVar1;
  FUN_00762e70(param_2 + 4);
  return param_1;
}

