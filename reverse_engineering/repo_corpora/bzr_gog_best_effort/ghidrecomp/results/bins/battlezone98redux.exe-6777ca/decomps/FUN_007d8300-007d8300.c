
void FUN_007d8300(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined1 *puVar7;
  undefined *puVar8;
  undefined2 *puVar9;
  undefined *puVar10;
  undefined1 local_2d8 [24];
  undefined1 local_2c0 [24];
  undefined1 local_2a8 [24];
  undefined1 local_290 [24];
  undefined1 local_278 [24];
  undefined1 local_260 [24];
  undefined1 local_248 [12];
  undefined1 local_23c [12];
  undefined1 local_230 [8];
  undefined1 local_228 [8];
  undefined1 local_220 [8];
  undefined1 local_218 [8];
  undefined1 local_210 [8];
  undefined1 local_208 [8];
  undefined1 local_200 [8];
  undefined1 local_1f8 [8];
  undefined1 local_1f0 [8];
  undefined1 local_1e8 [8];
  undefined1 local_1e0 [8];
  undefined1 local_1d8 [8];
  undefined1 local_1d0 [8];
  undefined1 local_1c8 [8];
  undefined1 local_1c0 [8];
  undefined1 local_1b8 [8];
  undefined1 local_1b0 [8];
  undefined1 local_1a8 [8];
  undefined1 local_1a0 [8];
  undefined1 local_198 [8];
  undefined1 local_190 [8];
  undefined1 local_188 [8];
  undefined1 local_180 [8];
  undefined1 local_178 [8];
  undefined1 local_170 [8];
  undefined1 local_168 [8];
  undefined1 local_160 [8];
  undefined1 local_158 [8];
  undefined1 local_150 [8];
  undefined1 local_148 [8];
  undefined1 local_140 [8];
  undefined1 local_138 [8];
  undefined1 local_130 [8];
  undefined1 local_128 [8];
  undefined1 local_120 [8];
  undefined1 local_118 [8];
  undefined1 local_110 [8];
  undefined1 local_108 [8];
  undefined1 local_100 [8];
  undefined1 local_f8 [8];
  undefined1 local_f0 [4];
  undefined1 local_ec [4];
  undefined1 local_e8 [4];
  undefined1 local_e4 [4];
  undefined1 local_e0 [4];
  undefined1 local_dc [4];
  undefined1 local_d8 [4];
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  undefined1 local_cc [4];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 local_af;
  undefined1 local_ae;
  undefined1 local_ad;
  undefined1 local_ac;
  undefined1 local_ab;
  undefined1 local_aa;
  undefined1 local_a9;
  int local_a8;
  undefined1 local_a4 [24];
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
  puStack_c = &LAB_00862ff6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_a8 + 0x2f0,local_a4);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  FUN_007d8c80();
  local_8._0_1_ = 3;
  FUN_007d9020();
  local_8._0_1_ = 4;
  FUN_007d9250();
  local_8._0_1_ = 5;
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 6;
  FUN_007d8ba0(local_8c);
  local_8._0_1_ = 8;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 9;
  FUN_007d8ba0(local_44);
  local_8._0_1_ = 0xb;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 0xc;
  FUN_007d8ba0(local_74);
  local_8._0_1_ = 0xe;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 0xf;
  FUN_007d8ba0(local_2c);
  local_8._0_1_ = 0x11;
  ~basic_string<>();
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 0x12;
  FUN_007d8ba0(local_5c);
  local_8 = CONCAT31(local_8._1_3_,0x14);
  ~basic_string<>();
  uVar2 = FUN_007d9860(local_1d8,&DAT_008767b4,0);
  uVar2 = FUN_007d98b0(local_1f0,&DAT_0260c015,uVar2);
  FUN_007d98d0(local_a8 + 0x230,uVar2);
  local_aa = 0;
  local_ad = 0;
  local_c8 = 1;
  local_af = 0;
  local_b4 = 1;
  puVar9 = &DAT_00871538;
  uVar2 = FUN_007d9a00(local_23c,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f,&local_aa);
  uVar2 = FUN_007d9980(local_cc,uVar2,puVar9);
  puVar7 = &local_ad;
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_200,&DAT_0260c048,&local_c8,&DAT_0260c07f,puVar7,uVar2);
  uVar2 = FUN_007d9910(local_2c0,&DAT_0260c08b,uVar2,puVar6,puVar7);
  uVar2 = FUN_007d9980(local_ec,uVar2);
  uVar3 = FUN_007d9860(local_210,&DAT_008848ac,0);
  uVar2 = FUN_007d98b0(local_220,uVar3,uVar2);
  uVar3 = FUN_007d99a0(local_230,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f);
  uVar2 = FUN_007d98b0(local_1a8,uVar3,uVar2);
  puVar7 = &local_af;
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_108,&DAT_0260c048,&local_b4,&DAT_0260c07f,puVar7,uVar2);
  uVar2 = FUN_007d9910(local_290,&DAT_0260c08b,uVar2,puVar6,puVar7);
  uVar2 = FUN_007d9980(local_d0,uVar2);
  uVar2 = FUN_007d98b0(local_1f8,uVar2);
  uVar2 = FUN_007d98b0(local_118,uVar2);
  uVar2 = FUN_007d9980(local_d8,uVar2);
  uVar3 = FUN_007d9860(local_1c8,&DAT_00871534,0);
  uVar2 = FUN_007d98b0(local_128,uVar3,uVar2);
  uVar2 = FUN_007d9a70(local_218,uVar2);
  FUN_007d9a90(local_a8 + 0x1f0,uVar2);
  puVar10 = &DAT_0260c039;
  uVar2 = FUN_007d99a0(local_138,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f);
  uVar3 = FUN_007d99a0(local_f8,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f);
  puVar8 = &DAT_0260c086;
  puVar6 = &DAT_0260c02e;
  iVar4 = local_a8 + 0x20;
  uVar5 = FUN_007d99a0(local_148,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f);
  uVar2 = FUN_007d98b0(local_208,uVar5,iVar4,puVar6,puVar8,uVar3,uVar2,puVar10);
  uVar2 = FUN_007d98b0(local_158,uVar2);
  uVar2 = FUN_007d98b0(local_1e8,uVar2);
  uVar2 = FUN_007d98b0(local_168,uVar2);
  uVar2 = FUN_007d98b0(local_1a0,uVar2);
  uVar2 = FUN_007d98b0(local_178,uVar2);
  FUN_007d9ab0(local_a8 + 0x270,uVar2);
  local_bc = 1;
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_1b0,&DAT_0260c048,&local_bc,&DAT_0260c07f);
  uVar2 = FUN_007d9b30(local_260,&DAT_0260c08b,uVar2,puVar6);
  uVar3 = FUN_007d9ad0(local_188,&DAT_0260c08b);
  uVar2 = FUN_007d9980(local_e0,uVar3,uVar2);
  puVar6 = &DAT_00896ce8;
  uVar3 = FUN_007d9ad0(local_1c0,&DAT_0260c08b);
  uVar2 = FUN_007d9980(local_e8,uVar3,puVar6,uVar2);
  uVar2 = FUN_007d98b0(local_198,local_a8 + 0x20,uVar2);
  uVar2 = FUN_007d9a70(local_1d0,uVar2);
  uVar2 = FUN_007d98b0(local_1e0,uVar2);
  uVar2 = FUN_007d98b0(local_228,uVar2);
  FUN_007d9b90(local_a8 + 0x2b0,uVar2);
  local_ae = 0;
  local_ac = 0;
  local_c4 = 1;
  local_ab = 0x2c;
  local_b8 = 1;
  local_a9 = 0;
  local_c0 = 1;
  puVar9 = &DAT_008949c4;
  uVar2 = FUN_007d9a00(local_248,&DAT_0260c08b,&DAT_0260c048,&DAT_0260c07f,&local_ae);
  uVar2 = FUN_007d9980(local_f0,uVar2,puVar9);
  puVar7 = &local_ac;
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_1b8,&DAT_0260c048,&local_c4,&DAT_0260c07f,puVar7,uVar2);
  uVar2 = FUN_007d9910(local_278,&DAT_0260c08b,uVar2,puVar6,puVar7);
  uVar2 = FUN_007d9980(local_d4,uVar2);
  uVar2 = FUN_007d9bb0(local_100,&local_ab,uVar2);
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_110,&DAT_0260c048,&local_b8,&DAT_0260c07f,uVar2);
  uVar2 = FUN_007d9b30(local_2a8,&DAT_0260c08b,uVar2,puVar6);
  uVar2 = FUN_007d98b0(local_120,uVar2);
  puVar7 = &local_a9;
  puVar6 = &DAT_0260c07f;
  uVar2 = FUN_007d98f0(local_130,&DAT_0260c048,&local_c0,&DAT_0260c07f,puVar7,uVar2);
  uVar2 = FUN_007d9910(local_2d8,&DAT_0260c08b,uVar2,puVar6,puVar7);
  uVar2 = FUN_007d9980(local_e4,uVar2);
  uVar2 = FUN_007d98b0(local_140,uVar2);
  uVar2 = FUN_007d9bd0(local_150,uVar2);
  uVar2 = FUN_007d9980(local_dc,uVar2);
  uVar3 = FUN_007d9860(local_160,&DAT_0087d198,0);
  uVar2 = FUN_007d98b0(local_170,uVar3,uVar2);
  uVar2 = FUN_007d98b0(local_180,uVar2);
  uVar2 = FUN_007d9a70(local_190,uVar2);
  FUN_007d9c10(local_a8 + 0x2f0,uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

