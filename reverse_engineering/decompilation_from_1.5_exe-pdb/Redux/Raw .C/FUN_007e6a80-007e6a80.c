
undefined1 FUN_007e6a80(void)

{
  undefined4 in_stack_00000024;
  undefined1 auStack_4c [32];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863568;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_11 = 0;
  uStack_28 = 0;
  uStack_2c = in_stack_00000024;
  local_1c = auStack_4c;
  local_20 = FUN_007dd560(&stack0x00000004);
  local_13 = FUN_007e8990();
  local_8 = 0xffffffff;
  uStack_28 = 0x7e6af1;
  local_12 = local_13;
  FUN_007db9d0();
  ExceptionList = local_10;
  return local_13;
}

