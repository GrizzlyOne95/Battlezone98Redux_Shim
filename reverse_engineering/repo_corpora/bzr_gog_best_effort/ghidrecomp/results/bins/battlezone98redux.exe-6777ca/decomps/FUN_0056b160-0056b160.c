
undefined1 FUN_0056b160(undefined4 *param_1,float *param_2,undefined4 *param_3,undefined1 param_4)

{
  undefined1 uVar1;
  
  uVar1 = FUN_0056af20(param_2,param_3,param_4);
  *param_1 = *param_3;
  param_1[1] = *param_2 * 4.9 + (float)param_3[1];
  param_1[2] = param_3[2];
  return uVar1;
}

