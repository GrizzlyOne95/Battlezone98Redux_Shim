
void FUN_007fbaa0(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 *puVar5;
  undefined *puVar6;
  undefined1 *puVar7;
  undefined *puVar8;
  undefined1 *puVar9;
  undefined *puVar10;
  undefined1 *puVar11;
  undefined *puVar12;
  undefined1 *puVar13;
  undefined *puVar14;
  undefined1 *puVar15;
  undefined *puVar16;
  undefined1 *puVar17;
  undefined1 local_cc [8];
  undefined1 local_c4 [8];
  undefined1 local_bc [8];
  undefined1 local_b4 [8];
  undefined1 local_ac [8];
  undefined1 local_a4 [8];
  undefined1 local_9c [8];
  undefined1 local_94 [8];
  undefined1 local_8c [8];
  undefined1 local_84 [8];
  undefined1 local_7c [7];
  undefined1 local_75 [2];
  undefined1 local_73 [2];
  undefined1 local_71 [2];
  undefined1 local_6f [2];
  undefined1 local_6d;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined1 local_6a;
  undefined1 local_69;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  int local_60;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008643f6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_60 + 0x20,local_44);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 3;
  FUN_007d8ba0(local_5c);
  local_8._0_1_ = 5;
  ~basic_string<>();
  basic_string<>("symbols");
  local_8._0_1_ = 6;
  FUN_007fbf60(local_2c);
  local_8 = CONCAT31(local_8._1_3_,8);
  ~basic_string<>();
  local_67 = 0x22;
  local_66 = 0x5c;
  local_69 = 0x2f;
  local_6b = 9;
  local_6d = 0xd;
  local_68 = 10;
  local_64 = 0xc;
  local_6c = 8;
  puVar17 = &local_67;
  puVar16 = &DAT_00899220;
  puVar15 = &local_66;
  puVar14 = &DAT_008a1b6c;
  puVar13 = &local_69;
  puVar12 = &DAT_008a1d88;
  puVar11 = &local_6b;
  puVar10 = &DAT_008a1b70;
  puVar9 = &local_6d;
  puVar8 = &DAT_008a1b74;
  puVar7 = &local_68;
  puVar6 = &DAT_008a1b78;
  puVar5 = &local_64;
  puVar4 = &DAT_008a1b34;
  FUN_007fc4c0(&DAT_008a1b38,&local_6c);
  FUN_007fc4c0(puVar4,puVar5);
  FUN_007fc4c0(puVar6,puVar7);
  FUN_007fc4c0(puVar8,puVar9);
  FUN_007fc4c0(puVar10,puVar11);
  FUN_007fc4c0(puVar12,puVar13);
  FUN_007fc4c0(puVar14,puVar15);
  FUN_007fc4c0(puVar16,puVar17);
  local_61 = 0x22;
  local_6a = 0x5c;
  local_62 = 0x22;
  local_63 = 0;
  local_65 = 0x22;
  uVar2 = FUN_007d9ce0(local_75,&local_61,0);
  puVar17 = &local_6a;
  uVar3 = FUN_007d9ce0(local_71,&local_62,0);
  uVar2 = FUN_007d9a70(local_b4,uVar3,puVar17,uVar2);
  uVar2 = FUN_007d98b0(local_ac,&DAT_0260c14d,uVar2);
  uVar3 = FUN_007d9ce0(local_6f,&local_63,0);
  uVar2 = FUN_007d9bb0(local_bc,&DAT_008a1d84,uVar3,uVar2);
  uVar2 = FUN_007d9bb0(local_cc,&DAT_008a1b64,&DAT_0260c0f5,uVar2);
  uVar2 = FUN_007d98b0(local_94,local_60 + 0x60,uVar2);
  uVar2 = FUN_007d98b0(local_84,uVar2);
  uVar2 = FUN_007d98b0(local_a4,uVar2);
  uVar2 = FUN_007d9980(local_7c,uVar2);
  uVar3 = FUN_007d9ce0(local_73,&local_65,0);
  uVar2 = FUN_007d98b0(local_c4,uVar3,uVar2);
  uVar2 = FUN_007d98b0(local_8c,uVar2);
  uVar2 = FUN_007d9bd0(local_9c,uVar2);
  FUN_007fc510(uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

