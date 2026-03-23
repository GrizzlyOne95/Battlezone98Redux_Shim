
undefined4 __thiscall FUN_00734570(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a188;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007347a0(param_2);
  local_8 = 0;
  allocator<>(param_1);
  ExceptionList = local_10;
  return param_1;
}

