
undefined4 FUN_0072f070(undefined4 param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00859b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007307e0(param_1);
  local_8 = 0xffffffff;
  FUN_004bb3b0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

