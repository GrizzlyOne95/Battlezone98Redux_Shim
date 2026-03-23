
undefined4 FUN_00728820(undefined4 param_1)

{
  char cVar1;
  byte *pbVar2;
  undefined4 uStack_90;
  undefined1 *puStack_8c;
  undefined4 uStack_88;
  undefined1 *puStack_84;
  undefined1 *puStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_78;
  undefined1 *puStack_74;
  uint uStack_70;
  undefined1 local_6c [8];
  undefined1 local_64 [8];
  undefined1 local_5c [8];
  undefined4 local_54;
  undefined1 *local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  undefined4 local_44;
  undefined1 *local_40;
  undefined4 local_3c;
  undefined1 *local_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  uint local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008593e0;
  local_10 = ExceptionList;
  uStack_70 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  local_8 = 2;
  puStack_74 = &stack0x00000014;
  puStack_78 = (undefined1 *)0x72885f;
  cVar1 = FID_conflict_operator__();
  if (cVar1 != '\0') {
    puStack_74 = &stack0x00000020;
    puStack_78 = (undefined1 *)0x728876;
    cVar1 = FID_conflict_operator__();
    if (cVar1 != '\0') {
      puStack_74 = &stack0x00000008;
      puStack_78 = &local_11;
      uStack_7c = 0x72888e;
      pbVar2 = (byte *)_Iter_cat<>();
      puStack_74 = (undefined1 *)(uint)*pbVar2;
      local_30 = (undefined1 *)&puStack_80;
      puStack_84 = &stack0x00000020;
      uStack_88 = 0x7288a8;
      local_34 = FUN_004bbb20();
      puStack_84 = local_5c;
      uStack_88 = 0x7288b4;
      local_1c = (undefined4 *)FUN_0072f070();
      puStack_78 = (undefined1 *)local_1c[1];
      uStack_7c = *local_1c;
      local_38 = (undefined1 *)&uStack_88;
      puStack_8c = &stack0x00000014;
      uStack_90 = 0x7288d5;
      local_3c = FUN_004bbb20();
      puStack_8c = local_64;
      uStack_90 = 0x7288e1;
      local_20 = (undefined4 *)FUN_0072f070();
      puStack_80 = (undefined1 *)local_20[1];
      puStack_84 = (undefined1 *)*local_20;
      local_40 = (undefined1 *)&uStack_90;
      local_44 = FUN_004bbb20(&stack0x00000008);
      local_24 = (undefined4 *)FUN_0072f070(local_6c);
      uStack_88 = local_24[1];
      puStack_8c = (undefined1 *)*local_24;
      uStack_90 = 0x728923;
      FUN_0072f130();
    }
  }
  local_48 = (undefined1 *)&uStack_7c;
  puStack_80 = &stack0x00000020;
  puStack_84 = (undefined1 *)0x728937;
  local_4c = FUN_004bbb20();
  local_8._0_1_ = 3;
  local_50 = (undefined1 *)&uStack_88;
  puStack_8c = &stack0x00000014;
  uStack_90 = 0x728955;
  local_28 = local_4c;
  local_54 = FUN_004bbb20();
  local_8._0_1_ = 2;
  puStack_8c = (undefined1 *)0x728961;
  puStack_74 = (undefined1 *)FUN_0072f180();
  puStack_78 = &stack0x00000008;
  uStack_7c = 0x728974;
  local_2c = puStack_74;
  advance<>();
  puStack_74 = &stack0x00000008;
  puStack_78 = (undefined1 *)0x728983;
  FUN_004bbb20();
  local_18 = local_18 | 1;
  local_8._0_1_ = 1;
  puStack_74 = (undefined1 *)0x728998;
  FUN_004bb3b0();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_74 = (undefined1 *)0x7289a4;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_74 = (undefined1 *)0x7289b3;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return param_1;
}

