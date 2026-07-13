
undefined4 FUN_007defa0(void)

{
  undefined1 auStack_54 [44];
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008635f8;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_28 = 0;
  local_18 = auStack_54;
  local_1c = FUN_007dd790(&stack0x00000004);
  local_20 = FUN_007df700();
  local_8 = 0xffffffff;
  uStack_28 = 0x7defff;
  FUN_007dba90();
  ExceptionList = local_10;
  return local_14;
}

