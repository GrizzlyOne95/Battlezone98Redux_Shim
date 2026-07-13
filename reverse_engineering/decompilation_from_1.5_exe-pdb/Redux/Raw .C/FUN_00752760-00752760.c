
undefined4 FUN_00752760(void)

{
  undefined1 auStack_38 [20];
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c0d8;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_24 = 0x752790;
  vector<>();
  local_8 = 0;
  uStack_24 = 0x75279c;
  FUN_00764790();
  uStack_24 = 0x7527a3;
  FUN_007682a0();
  local_18 = auStack_38;
  local_1c = basic_string<>("All Maps");
  FUN_00752a50();
  ExceptionList = local_10;
  return local_14;
}

