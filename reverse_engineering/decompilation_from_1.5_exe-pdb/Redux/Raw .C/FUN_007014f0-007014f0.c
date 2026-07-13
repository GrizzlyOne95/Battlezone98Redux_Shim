
undefined4 __thiscall FUN_007014f0(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008566f8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  make_error_code(param_2,0x17,DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_2;
}

