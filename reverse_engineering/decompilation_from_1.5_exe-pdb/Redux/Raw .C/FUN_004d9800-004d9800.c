
undefined4 * __thiscall FUN_004d9800(undefined4 *param_1,undefined4 param_2)

{
  int local_c;
  
  *param_1 = param_2;
  for (local_c = 0; local_c < 5; local_c = local_c + 1) {
    param_1[local_c + 1] = 0;
    param_1[local_c + 6] = 0;
  }
  param_1[0xb] = 0;
  param_1[0xd] = 0;
  param_1[0xc] = 0;
  param_1[0xe] = 0xffffffff;
  return param_1;
}

