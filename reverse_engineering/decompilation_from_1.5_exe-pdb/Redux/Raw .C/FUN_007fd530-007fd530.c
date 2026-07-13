
undefined4 FUN_007fd530(void)

{
  undefined1 auStack_60 [56];
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00864618;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_28 = 0;
  local_18 = auStack_60;
  local_1c = FUN_007fc680(&stack0x00000004);
  local_20 = FUN_007febe0();
  local_8 = 0xffffffff;
  uStack_28 = 0x7fd58f;
  CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)&stack0x00000004);
  ExceptionList = local_10;
  return local_14;
}

