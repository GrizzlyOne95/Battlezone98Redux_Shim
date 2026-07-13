
void FUN_007fc310(int param_1)

{
  int iStack_a8;
  undefined1 auStack_a4 [24];
  undefined4 uStack_8c;
  undefined1 *puStack_88;
  undefined1 auStack_84 [16];
  undefined4 uStack_74;
  uint uStack_70;
  CTraceSnapshot local_6c [56];
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008644b8;
  local_10 = ExceptionList;
  uStack_70 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_20 = auStack_84;
  puStack_88 = &stack0x00000008;
  uStack_8c = 0x7fc34d;
  local_24 = FUN_007fc640();
  local_8._0_1_ = 1;
  iStack_a8 = param_1 + 0x20;
  local_28 = auStack_a4;
  local_14 = local_24;
  local_2c = FUN_007fc750();
  local_8._0_1_ = 0;
  iStack_a8 = 0x7fc37d;
  local_1c = FUN_007fc820();
  local_8._0_1_ = 2;
  local_30 = (undefined1 *)&iStack_a8;
  local_18 = local_1c;
  local_34 = FUN_007fc680(local_1c);
  FUN_007fcd20();
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_74 = 0x7fc3b5;
  CTraceSnapshot::~CTraceSnapshot(local_6c);
  local_8 = 0xffffffff;
  uStack_74 = 0x7fc3c4;
  FUN_007fb7c0();
  ExceptionList = local_10;
  return;
}

