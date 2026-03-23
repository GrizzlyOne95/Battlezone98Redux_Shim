
void FUN_007289d0(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_68 [4];
  undefined4 uStack_64;
  undefined1 *puStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined1 *puStack_54;
  uint uStack_50;
  undefined1 *local_4c;
  undefined1 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859420;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  local_4c = (undefined1 *)&uStack_5c;
  puStack_60 = &stack0x00000018;
  uStack_64 = 0x728a13;
  local_14 = uStack_50;
  local_3c = FUN_004bbb20();
  local_8._0_1_ = 2;
  local_48 = auStack_68;
  local_34 = local_3c;
  local_40 = FUN_004bbb20(&stack0x0000000c);
  local_8._0_1_ = 1;
  local_44 = FUN_0072f270();
  local_8._0_1_ = 3;
  puStack_54 = local_2c;
  uStack_58 = param_2;
  uStack_5c = param_1;
  puStack_60 = (undefined1 *)0x728a5b;
  FUN_0072b490();
  local_38 = local_30;
  local_8._0_1_ = 1;
  puStack_54 = (undefined1 *)0x728a6d;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_54 = (undefined1 *)0x728a79;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_54 = (undefined1 *)0x728a88;
  FUN_004bb3b0();
  ExceptionList = local_10;
  uStack_50 = 0x728aa0;
  FUN_0083e885();
  return;
}

