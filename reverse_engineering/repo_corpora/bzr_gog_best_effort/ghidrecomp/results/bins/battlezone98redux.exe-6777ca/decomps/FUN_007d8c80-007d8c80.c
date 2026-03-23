
void FUN_007d8c80(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined **ppuVar6;
  undefined1 *puVar7;
  undefined **ppuVar8;
  undefined1 *puVar9;
  undefined **ppuVar10;
  undefined1 *puVar11;
  undefined **ppuVar12;
  undefined1 *puVar13;
  undefined **ppuVar14;
  undefined1 *puVar15;
  undefined **ppuVar16;
  undefined1 local_f8 [8];
  undefined1 local_f0 [8];
  undefined1 local_e8 [8];
  undefined1 local_e0 [8];
  undefined1 local_d8 [8];
  undefined1 local_d0 [8];
  undefined1 local_c8 [8];
  undefined1 local_c0 [4];
  undefined *local_bc;
  undefined *local_b8;
  undefined *local_b4;
  undefined *local_b0;
  undefined *local_ac;
  undefined1 local_a8 [2];
  undefined1 local_a6 [2];
  undefined *local_a4;
  undefined *local_a0;
  undefined1 local_99;
  undefined1 local_98;
  undefined1 local_97;
  undefined1 local_96;
  undefined1 local_95;
  undefined1 local_94;
  undefined1 local_93;
  undefined1 local_92;
  undefined1 local_91;
  int local_90;
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008630c4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_90 + 0xd0,local_5c);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  basic_string<>("symbols");
  local_8._0_1_ = 3;
  FUN_007d9470(local_8c);
  local_8._0_1_ = 5;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 6;
  FUN_007d8ba0(local_44);
  local_8._0_1_ = 8;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 9;
  FUN_007d8ba0(local_2c);
  local_8._0_1_ = 0xb;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 0xc;
  FUN_007d8ba0(local_74);
  local_8 = CONCAT31(local_8._1_3_,0xe);
  ~basic_string<>();
  local_b0 = &DAT_00899220;
  local_92 = 0x22;
  local_b8 = &DAT_008a1b6c;
  local_96 = 0x5c;
  local_bc = &DAT_008a1b70;
  local_98 = 9;
  local_a0 = &DAT_008a1b74;
  local_93 = 0xd;
  local_a4 = &DAT_008a1b78;
  local_95 = 10;
  local_b4 = &DAT_008a1b34;
  local_97 = 0xc;
  local_ac = &DAT_008a1b38;
  local_99 = 8;
  ppuVar16 = &local_b0;
  puVar15 = &local_92;
  ppuVar14 = &local_b8;
  puVar13 = &local_96;
  ppuVar12 = &local_bc;
  puVar11 = &local_98;
  ppuVar10 = &local_a0;
  puVar9 = &local_93;
  ppuVar8 = &local_a4;
  puVar7 = &local_95;
  ppuVar6 = &local_b4;
  puVar5 = &local_97;
  FUN_007d9c50(&local_99,&local_ac);
  FUN_007d9c50(puVar5,ppuVar6);
  FUN_007d9c50(puVar7,ppuVar8);
  FUN_007d9c50(puVar9,ppuVar10);
  FUN_007d9c50(puVar11,ppuVar12);
  FUN_007d9c50(puVar13,ppuVar14);
  FUN_007d9c50(puVar15,ppuVar16);
  uVar2 = FUN_007d9bb0(local_d8,&DAT_008a1b64,&DAT_0260c042);
  uVar2 = FUN_007d98b0(local_e0,local_90 + 0x20,&DAT_0260c01c,&DAT_0260c08e,uVar2);
  uVar2 = FUN_007d98b0(local_d0,uVar2);
  uVar2 = FUN_007d98b0(local_c8,uVar2);
  FUN_007d9c90(local_90 + 0x50,uVar2);
  uVar2 = FUN_007d9980(local_c0,local_90 + 0x50);
  FUN_007d9cb0(uVar2);
  local_91 = 0x22;
  local_94 = 0x22;
  uVar2 = FUN_007d9ce0(local_a8,&local_91,0);
  iVar3 = local_90 + 0x90;
  uVar4 = FUN_007d9ce0(local_a6,&local_94,0);
  uVar2 = FUN_007d98b0(local_e8,uVar4,iVar3,uVar2);
  uVar2 = FUN_007d98b0(local_f8,uVar2);
  uVar2 = FUN_007d9bd0(local_f0,uVar2);
  FUN_007d9d30(local_90 + 0xd0,uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

