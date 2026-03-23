
undefined4 FUN_007dca10(void)

{
  undefined1 auStack_80 [44];
  undefined4 uStack_54;
  undefined4 uStack_50;
  uint uStack_4c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008633a0;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_54 = 0;
  local_24 = auStack_80;
  local_28 = FUN_007dd790(&stack0x00000004);
  local_1c = FUN_007defa0();
  local_8._0_1_ = 1;
  uStack_54 = 0x7dca76;
  local_18 = local_1c;
  FUN_007ddb70();
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_50 = 0x7dca82;
  FUN_007d7950();
  local_20 = local_14;
  local_8 = 0xffffffff;
  uStack_50 = 0x7dca97;
  FUN_007dba90();
  ExceptionList = local_10;
  return local_20;
}

