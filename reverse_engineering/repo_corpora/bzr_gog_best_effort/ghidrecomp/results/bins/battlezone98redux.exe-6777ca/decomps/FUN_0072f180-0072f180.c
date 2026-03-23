
undefined4 FUN_0072f180(void)

{
  byte *pbVar1;
  undefined1 auStack_54 [4];
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined1 auStack_48 [8];
  undefined4 uStack_40;
  undefined4 *puStack_3c;
  undefined1 *puStack_38;
  uint uStack_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859bb8;
  local_10 = ExceptionList;
  uStack_34 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  local_18 = 0;
  puStack_38 = &stack0x00000004;
  puStack_3c = (undefined4 *)&local_11;
  uStack_40 = 0x72f1c0;
  pbVar1 = (byte *)_Iter_cat<>();
  puStack_38 = (undefined1 *)(uint)*pbVar1;
  puStack_3c = &local_18;
  local_24 = auStack_48;
  puStack_4c = &stack0x00000010;
  uStack_50 = 0x72f1de;
  local_28 = FUN_004bbb20();
  local_8._0_1_ = 2;
  local_2c = auStack_54;
  local_1c = local_28;
  local_30 = FUN_004bbb20(&stack0x00000004);
  local_8._0_1_ = 1;
  FUN_007311e0();
  local_20 = local_18;
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_38 = (undefined1 *)0x72f21d;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_38 = (undefined1 *)0x72f22c;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return local_20;
}

