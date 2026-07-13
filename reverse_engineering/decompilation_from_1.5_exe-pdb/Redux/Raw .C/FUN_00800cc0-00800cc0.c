
undefined1 FUN_00800cc0(void)

{
  undefined4 in_stack_0000003c;
  undefined1 auStack_64 [56];
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
  
  puStack_c = &LAB_00864618;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_11 = 0;
  uStack_28 = 0;
  uStack_2c = in_stack_0000003c;
  local_1c = auStack_64;
  local_20 = FUN_007fc680(&stack0x00000004);
  local_13 = FUN_008037e0();
  local_8 = 0xffffffff;
  uStack_28 = 0x800d31;
  local_12 = local_13;
  CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)&stack0x00000004);
  ExceptionList = local_10;
  return local_13;
}

