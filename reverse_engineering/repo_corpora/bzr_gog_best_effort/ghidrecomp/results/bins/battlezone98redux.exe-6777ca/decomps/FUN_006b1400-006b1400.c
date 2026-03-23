
undefined4 * __thiscall FUN_006b1400(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  *param_1 = param_2;
  uVar1 = FUN_006ac540(param_2);
  param_1[1] = uVar1;
  param_1[2] = 0;
  param_1[3] = 0;
  FUN_006ac110();
  param_1[10] = 0;
  return param_1;
}

