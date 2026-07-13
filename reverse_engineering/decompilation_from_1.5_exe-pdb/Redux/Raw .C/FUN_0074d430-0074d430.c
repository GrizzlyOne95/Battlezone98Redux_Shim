
undefined4 __thiscall FUN_0074d430(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008526c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  <>(param_2);
  local_8 = 0;
  FUN_006cd7b0(param_1);
  local_8 = 0xffffffff;
  FUN_006676c0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

