
void FUN_00728740(void)

{
  byte *pbVar1;
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  uint uStack_40;
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined1 local_12;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008593a0;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  puStack_44 = &stack0x00000004;
  puStack_48 = &local_12;
  uStack_4c = 0x728779;
  pbVar1 = (byte *)_Iter_cat<>();
  local_11 = *pbVar1;
  puStack_44 = (undefined1 *)(uint)local_11;
  local_20 = (undefined1 *)&uStack_50;
  puStack_54 = &stack0x00000010;
  uStack_58 = 0x728797;
  local_24 = FUN_004bbb20();
  puStack_54 = local_34;
  uStack_58 = 0x7287a3;
  local_18 = (undefined4 *)FUN_0072f070();
  puStack_48 = (undefined1 *)local_18[1];
  uStack_4c = *local_18;
  local_28 = (undefined1 *)&uStack_58;
  local_2c = FUN_004bbb20(&stack0x00000004);
  local_1c = (undefined4 *)FUN_0072f070(local_3c);
  uStack_50 = local_1c[1];
  puStack_54 = (undefined1 *)*local_1c;
  uStack_58 = 0x7287e5;
  FUN_0072f0d0();
  local_8 = local_8 & 0xffffff00;
  puStack_44 = (undefined1 *)0x7287f4;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_44 = (undefined1 *)0x728803;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

