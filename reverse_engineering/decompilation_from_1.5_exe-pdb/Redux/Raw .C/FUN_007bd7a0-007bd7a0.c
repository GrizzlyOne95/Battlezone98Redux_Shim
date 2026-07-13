
undefined4 * FUN_007bd7a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000018;
  undefined4 uStack_68;
  undefined1 *puStack_64;
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 *puStack_54;
  undefined4 uStack_50;
  uint uStack_4c;
  undefined1 local_44 [4];
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined1 *local_24;
  undefined1 local_20 [4];
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00861a18;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  uStack_50 = in_stack_00000018;
  puStack_54 = (undefined4 *)local_20;
  uStack_58 = 0x7bd7da;
  puVar1 = (undefined4 *)FUN_0042ef30();
  uStack_50 = *puVar1;
  local_24 = (undefined1 *)&uStack_58;
  local_28 = auStack_60;
  puStack_64 = &stack0x00000010;
  uStack_68 = 0x7bd7f9;
  local_2c = FUN_006676e0();
  uStack_68 = 0x7bd802;
  puStack_64 = (undefined1 *)&uStack_58;
  local_30 = FUN_007bdae0();
  local_8._0_1_ = 2;
  local_34 = auStack_60;
  local_38 = (undefined1 *)&uStack_68;
  local_14 = local_30;
  local_3c = FUN_006676e0(&stack0x00000008);
  local_40 = FUN_007bdae0(auStack_60);
  puStack_64 = local_44;
  local_8._0_1_ = 1;
  uStack_68 = 0x7bd84d;
  local_18 = local_40;
  local_1c = (undefined4 *)FUN_007bdb50();
  uStack_50 = *local_1c;
  puStack_54 = &stack0x00000018;
  uStack_58 = 0x7bd862;
  puVar1 = (undefined4 *)FUN_0042ef30();
  *param_1 = *puVar1;
  local_8 = (uint)local_8._1_3_ << 8;
  uStack_50 = 0x7bd878;
  FUN_00667660();
  local_8 = 0xffffffff;
  uStack_50 = 0x7bd887;
  FUN_00667660();
  ExceptionList = local_10;
  return param_1;
}

