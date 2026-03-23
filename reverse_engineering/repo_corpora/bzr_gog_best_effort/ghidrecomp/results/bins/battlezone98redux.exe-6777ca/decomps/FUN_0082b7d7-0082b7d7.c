
undefined4 FUN_0082b7d7(undefined4 param_1,undefined4 *param_2,int *param_3)

{
  if (param_2[1] == 0) {
    return 0;
  }
  *param_3 = param_2[1];
  param_2[1] = 0;
  return *param_2;
}

