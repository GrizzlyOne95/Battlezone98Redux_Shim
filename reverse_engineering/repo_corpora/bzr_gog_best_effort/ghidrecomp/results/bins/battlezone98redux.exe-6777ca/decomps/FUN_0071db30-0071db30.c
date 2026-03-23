
undefined4 __thiscall FUN_0071db30(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858878;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0071e9e0(param_2);
  local_8 = 0;
  allocator<>(param_1);
  ExceptionList = local_10;
  return param_1;
}

