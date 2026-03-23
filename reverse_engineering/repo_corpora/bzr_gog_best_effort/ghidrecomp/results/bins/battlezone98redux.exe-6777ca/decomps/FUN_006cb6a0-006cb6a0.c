
undefined4 FUN_006cb6a0(undefined4 param_1)

{
  undefined4 uStack_8c;
  undefined1 *puStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined1 *puStack_7c;
  code *pcStack_78;
  undefined4 uStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;
  code *pcStack_68;
  uint uStack_64;
  undefined1 local_60 [24];
  code *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 *local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852958;
  local_10 = ExceptionList;
  uStack_64 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  local_8 = 0;
  local_48 = FUN_006cfad0;
  local_44 = 0;
  pcStack_68 = _1_exref;
  puStack_6c = &stack0x00000008;
  puStack_70 = local_1c;
  uStack_74 = 0;
  pcStack_78 = FUN_006cfad0;
  puStack_7c = local_60;
  uStack_80 = 0x6cb70a;
  uStack_80 = FUN_006dcc50();
  local_8._0_1_ = 1;
  local_2c = (undefined1 *)&puStack_7c;
  uStack_84 = 0x6cb72b;
  local_24 = uStack_80;
  local_20 = uStack_80;
  local_30 = FUN_006dccb0();
  local_8._0_1_ = 2;
  local_34 = (undefined1 *)&uStack_84;
  puStack_88 = (undefined1 *)&uStack_84;
  uStack_8c = 0x6cb749;
  local_28 = local_30;
  FUN_00421ec0();
  uStack_8c = 0x6cb750;
  local_38 = FUN_006daea0();
  local_3c = (undefined1 *)&uStack_8c;
  local_40 = FUN_006dcc30(&uStack_8c,&stack0x00000008);
  local_8._0_1_ = 1;
  FUN_006d00a0();
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_68 = (code *)0x6cb783;
  ~<>();
  pcStack_68 = (code *)&stack0x00000008;
  puStack_6c = (undefined1 *)0x6cb78f;
  shared_ptr<>();
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  pcStack_68 = (code *)0x6cb7a7;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

