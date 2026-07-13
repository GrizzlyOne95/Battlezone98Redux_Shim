
undefined4 __thiscall FUN_006f49e0(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008555a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006f4320(param_2);
  local_8 = 0;
  allocator<>(param_1);
  ExceptionList = local_10;
  return param_1;
}

