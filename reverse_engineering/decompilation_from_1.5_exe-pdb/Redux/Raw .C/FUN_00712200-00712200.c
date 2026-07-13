
undefined4 __thiscall FUN_00712200(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857cd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007129b0(param_2);
  local_8 = 0;
  allocator<>(param_1);
  ExceptionList = local_10;
  return param_1;
}

