
undefined4 FUN_0076f450(undefined4 param_1)

{
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  uint uStack_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085ddd0;
  local_10 = ExceptionList;
  uStack_34 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  local_8 = 0;
  local_20 = auStack_40;
  puStack_48 = auStack_40;
  uStack_44 = 1;
  uStack_4c = 0x76f499;
  local_24 = FID_conflict_operator_();
  local_8._0_1_ = 1;
  local_28 = (undefined1 *)&uStack_4c;
  local_18 = local_24;
  local_2c = _String_const_iterator<>(&stack0x00000008);
  local_8 = (uint)local_8._1_3_ << 8;
  local_30 = FUN_0076faf0(param_1);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  uStack_38 = 0x76f4e5;
  FUN_004bb3d0();
  ExceptionList = local_10;
  return param_1;
}

