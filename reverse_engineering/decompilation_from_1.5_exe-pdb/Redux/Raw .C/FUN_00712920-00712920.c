
undefined4 * __thiscall FUN_00712920(undefined4 *param_1,undefined4 *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085524b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = *param_2;
  FUN_00713b90(param_2 + 1);
  local_8 = 0;
  param_1[9] = param_2[9];
  param_1[10] = param_2[10];
  FUN_006f6450(param_2 + 0xc);
  ExceptionList = local_10;
  return param_1;
}

