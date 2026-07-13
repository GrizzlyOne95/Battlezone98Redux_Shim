
undefined4 * __thiscall
FUN_00704450(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,
            undefined4 param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085524b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  allocator<>(param_4);
  *param_1 = param_2;
  FUN_006f6570(param_3);
  local_8 = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  FUN_00705510(param_5);
  ExceptionList = local_10;
  return param_1;
}

