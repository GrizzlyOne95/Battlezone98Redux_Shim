
undefined4 * __thiscall FUN_00712a40(undefined4 *param_1,undefined4 *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085527b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  basic_string<>(param_2 + 2);
  local_8 = 0;
  param_1[8] = param_2[8];
  param_1[9] = param_2[9];
  FUN_006f6500(param_2 + 10);
  ExceptionList = local_10;
  return param_1;
}

