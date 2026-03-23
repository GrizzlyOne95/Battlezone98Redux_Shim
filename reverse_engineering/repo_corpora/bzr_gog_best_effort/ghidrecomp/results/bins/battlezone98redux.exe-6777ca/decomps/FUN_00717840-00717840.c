
void FUN_00717840(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_48 [4];
  undefined4 uStack_44;
  undefined1 *puStack_40;
  undefined1 auStack_3c [8];
  undefined4 uStack_34;
  uint uStack_30;
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008581a8;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  local_18 = param_2;
  local_1c = auStack_3c;
  puStack_40 = &stack0x00000018;
  uStack_44 = 0x717883;
  local_20 = FUN_004bbb20();
  local_8._0_1_ = 2;
  local_24 = auStack_48;
  local_14 = local_20;
  local_28 = FUN_004bbb20(&stack0x0000000c);
  local_8._0_1_ = 1;
  FUN_00723810(local_2c,local_18);
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_34 = 0x7178c4;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  uStack_34 = 0x7178d3;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

