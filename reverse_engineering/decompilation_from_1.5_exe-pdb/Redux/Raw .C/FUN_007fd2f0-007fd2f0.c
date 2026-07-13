
undefined4 FUN_007fd2f0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_34 [20];
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008645e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = 0;
  local_20 = FUN_007fdfd0(local_34,param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  local_1c = local_20;
  uVar1 = FUN_00422f60(local_20);
  FUN_007fc730(uVar1);
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  FUN_007fb7a0();
  ExceptionList = local_10;
  return param_1;
}

