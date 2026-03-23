
undefined4 FUN_007df640(void)

{
  undefined1 auStack_9c [120];
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008636b8;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_24 = 0x7df677;
  FUN_00423890();
  local_18 = auStack_9c;
  local_1c = FUN_007dd770(&stack0x00000004);
  FUN_007e2a70();
  local_8 = 0xffffffff;
  uStack_24 = 0x7df6a2;
  FUN_007dba50();
  ExceptionList = local_10;
  return local_14;
}

