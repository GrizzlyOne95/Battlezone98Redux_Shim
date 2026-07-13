
undefined4 FUN_00770c20(undefined4 param_1)

{
  undefined1 auStack_68 [4];
  undefined4 uStack_64;
  undefined1 *puStack_60;
  undefined1 auStack_5c [4];
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined1 auStack_50 [4];
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  uint uStack_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085df88;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  local_8 = 2;
  puStack_44 = &stack0x00000020;
  puStack_48 = &stack0x00000008;
  uStack_4c = 0x770c60;
  local_11 = _Ptr_cat<>();
  puStack_44 = (undefined1 *)(uint)local_11;
  local_24 = auStack_50;
  puStack_54 = &stack0x00000020;
  uStack_58 = 0x770c7c;
  local_28 = FUN_004bbb20();
  local_8._0_1_ = 3;
  local_2c = auStack_5c;
  puStack_60 = &stack0x00000014;
  uStack_64 = 0x770c9a;
  local_1c = local_28;
  local_30 = FUN_004bbb20();
  local_8._0_1_ = 4;
  local_34 = auStack_68;
  local_20 = local_30;
  local_38 = FUN_004bbb20(&stack0x00000008);
  local_8._0_1_ = 2;
  local_3c = FUN_00771240(param_1);
  local_18 = local_18 | 1;
  local_8._0_1_ = 1;
  puStack_44 = (undefined1 *)0x770ce3;
  FUN_004bb3b0();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_44 = (undefined1 *)0x770cef;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_44 = (undefined1 *)0x770cfe;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return param_1;
}

