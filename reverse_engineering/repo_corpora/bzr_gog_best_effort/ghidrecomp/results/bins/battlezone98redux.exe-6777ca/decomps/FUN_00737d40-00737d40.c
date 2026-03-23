
undefined4 __thiscall FUN_00737d40(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a6e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00737ab0(param_2);
  local_8 = 0;
  allocator<>(param_1);
  ExceptionList = local_10;
  return param_1;
}

