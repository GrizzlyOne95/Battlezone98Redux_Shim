
undefined4 * FUN_00450100(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  while (param_1 != param_2) {
    param_2 = param_2 + -1;
    param_3 = param_3 + -1;
    *param_3 = *param_2;
  }
  return param_3;
}

