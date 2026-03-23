
undefined4 FUN_0076faf0(undefined4 param_1)

{
  uint uVar1;
  undefined1 auStack_118 [4];
  undefined4 uStack_114;
  undefined1 *puStack_110;
  undefined1 auStack_10c [4];
  undefined4 uStack_108;
  undefined1 *puStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined1 *puStack_f8;
  uint uStack_f4;
  undefined1 local_f0 [12];
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  undefined4 local_b4;
  undefined4 local_b0;
  undefined1 *local_ac;
  undefined1 *local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined1 *local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined1 *local_8c;
  undefined4 local_88;
  undefined1 *local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 local_64 [12];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40 [12];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  char local_15;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085de4c;
  local_10 = ExceptionList;
  uStack_f4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_28 = 0;
  local_8 = 1;
  local_ac = (undefined1 *)&uStack_100;
  puStack_104 = &stack0x00000008;
  uStack_108 = 0x76fb3d;
  local_98 = _String_const_iterator<>();
  puStack_104 = local_40;
  uStack_108 = 0x76fb4f;
  local_a0 = FID_conflict__Make_iter();
  local_8._0_1_ = 2;
  local_9c = (undefined1 *)&uStack_100;
  puStack_104 = &stack0x00000014;
  uStack_108 = 0x76fb6d;
  local_74 = _String_const_iterator<>();
  puStack_104 = local_64;
  uStack_108 = 0x76fb7c;
  local_68 = FID_conflict__Make_iter();
  local_8._0_1_ = 3;
  puStack_f8 = local_c0;
  uStack_fc = 0x76fb92;
  puStack_f8 = (undefined1 *)FUN_004bb540();
  local_8._0_1_ = 4;
  uStack_fc = 0x76fbab;
  local_58 = puStack_f8;
  local_54 = puStack_f8;
  local_20 = FUN_00732e10();
  local_8._0_1_ = 3;
  puStack_f8 = (undefined1 *)0x76fbbd;
  FUN_004bb3b0();
  puStack_f8 = local_40;
  uStack_fc = 0x76fbc9;
  local_1c = FUN_00732e10();
  puStack_f8 = local_e4;
  uStack_fc = 0x76fbdb;
  local_50 = FUN_004bb570();
  local_8._0_1_ = 5;
  puStack_f8 = local_64;
  uStack_fc = 0x76fbf4;
  local_2c = local_50;
  uVar1 = FUN_00732e10();
  local_15 = local_20 < uVar1;
  local_24 = (uint)(byte)local_15;
  local_8._0_1_ = 3;
  puStack_f8 = (undefined1 *)0x76fc1e;
  FUN_004bb3b0();
  if (local_15 == '\0') {
    local_a8 = (undefined1 *)&uStack_100;
    puStack_104 = local_40;
    uStack_108 = 0x76fcd4;
    local_6c = FUN_004bbb20();
    local_8._0_1_ = 7;
    local_70 = auStack_10c;
    puStack_110 = auStack_10c;
    uStack_114 = 0x76fcf2;
    local_30 = local_6c;
    local_78 = FUN_004bb570();
    local_8._0_1_ = 8;
    local_80 = auStack_118;
    local_34 = local_78;
    local_88 = FUN_004bbb20(local_64);
    local_8 = CONCAT31(local_8._1_3_,3);
    local_90 = FUN_00770d10(local_d8);
    puStack_f8 = (undefined1 *)0x76fd3a;
    FUN_004bb3b0();
    for (; local_1c != 0; local_1c = local_1c + -1) {
      puStack_f8 = (undefined1 *)0x76fd53;
      FUN_00770740();
    }
  }
  else {
    local_7c = (undefined1 *)&uStack_100;
    puStack_104 = local_64;
    uStack_108 = 0x76fc3b;
    local_a4 = FUN_004bbb20();
    local_8._0_1_ = 6;
    local_84 = auStack_10c;
    puStack_110 = local_40;
    uStack_114 = 0x76fc5c;
    local_48 = local_a4;
    local_b4 = FUN_004bbb20();
    local_8c = auStack_118;
    local_b0 = FUN_004bb540(auStack_118);
    local_8 = CONCAT31(local_8._1_3_,3);
    local_94 = FUN_00770c20(local_cc);
    puStack_f8 = (undefined1 *)0x76fca0;
    FUN_004bb3b0();
    for (; local_1c != 0; local_1c = local_1c + -1) {
      puStack_f8 = (undefined1 *)0x76fcb9;
      FUN_007706b0();
    }
  }
  puStack_f8 = local_f0;
  uStack_fc = 0x76fd64;
  local_4c = FUN_004bb540();
  local_8._0_1_ = 9;
  puStack_f8 = (undefined1 *)local_20;
  uStack_fc = param_1;
  uStack_100 = 0x76fd81;
  local_44 = local_4c;
  FID_conflict_operator_();
  local_28 = local_28 | 1;
  local_8._0_1_ = 3;
  puStack_f8 = (undefined1 *)0x76fd99;
  FUN_004bb3b0();
  local_8._0_1_ = 2;
  puStack_f8 = (undefined1 *)0x76fda5;
  FUN_004bb3b0();
  local_8._0_1_ = 1;
  puStack_f8 = (undefined1 *)0x76fdb1;
  FUN_004bb3b0();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_f8 = (undefined1 *)0x76fdbd;
  FUN_004bb3d0();
  local_8 = 0xffffffff;
  puStack_f8 = (undefined1 *)0x76fdcc;
  FUN_004bb3d0();
  ExceptionList = local_10;
  return param_1;
}

