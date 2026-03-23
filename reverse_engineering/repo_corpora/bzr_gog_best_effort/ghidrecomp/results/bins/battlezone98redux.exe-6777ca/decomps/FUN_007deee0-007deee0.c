
undefined4 FUN_007deee0(void)

{
  undefined1 auStack_a4 [124];
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008635c8;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_28 = 0;
  local_18 = auStack_a4;
  local_1c = FUN_007dd770(&stack0x00000004);
  local_20 = FUN_007df640();
  local_8 = 0xffffffff;
  uStack_28 = 0x7def3f;
  FUN_007dba50();
  ExceptionList = local_10;
  return local_14;
}

