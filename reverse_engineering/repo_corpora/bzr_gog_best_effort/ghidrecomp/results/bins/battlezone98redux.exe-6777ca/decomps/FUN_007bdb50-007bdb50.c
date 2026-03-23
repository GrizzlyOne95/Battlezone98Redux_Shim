
undefined4 FUN_007bdb50(undefined4 param_1)

{
  undefined4 in_stack_00000018;
  undefined4 uStack_44;
  undefined1 *puStack_40;
  undefined1 auStack_3c [4];
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined4 *puStack_30;
  uint uStack_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00861a98;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  puStack_30 = &stack0x00000018;
  puStack_34 = &stack0x00000008;
  uStack_38 = 0x7bdb89;
  local_11 = _Ptr_cat<>();
  puStack_30 = (undefined4 *)(uint)local_11;
  puStack_34 = (undefined1 *)in_stack_00000018;
  local_1c = auStack_3c;
  puStack_40 = &stack0x00000010;
  uStack_44 = 0x7bdba9;
  local_20 = FUN_006676e0();
  local_8._0_1_ = 2;
  local_24 = (undefined1 *)&uStack_44;
  local_18 = local_20;
  local_28 = FUN_006676e0(&stack0x00000008);
  local_8._0_1_ = 1;
  FUN_007bdf00(param_1);
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_30 = (undefined4 *)0x7bdbe6;
  FUN_00667660();
  local_8 = 0xffffffff;
  puStack_30 = (undefined4 *)0x7bdbf5;
  FUN_00667660();
  ExceptionList = local_10;
  return param_1;
}

