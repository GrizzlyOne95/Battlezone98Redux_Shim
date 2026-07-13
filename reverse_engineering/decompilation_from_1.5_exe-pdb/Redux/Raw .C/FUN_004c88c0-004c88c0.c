
void __thiscall FUN_004c88c0(int param_1,undefined4 param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  undefined1 local_2d8 [12];
  undefined1 local_2cc [12];
  undefined1 local_2c0 [12];
  undefined1 local_2b4 [12];
  undefined1 local_2a8 [12];
  undefined1 local_29c [12];
  undefined1 local_290 [12];
  undefined1 local_284 [12];
  undefined1 local_278 [12];
  undefined1 local_26c [12];
  undefined1 local_260 [12];
  undefined1 local_254 [12];
  undefined1 local_248 [12];
  undefined1 local_23c [12];
  undefined1 local_230 [12];
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  uint local_210;
  int local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc [16];
  float local_18c [4];
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  double local_164;
  double local_15c;
  double local_154;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20c = param_1;
  for (local_210 = param_1 + 0x28; local_210 < *(uint *)(local_20c + 0x1228);
      local_210 = local_210 + 0x48) {
    pfVar1 = (float *)FUN_0081fe60();
    pfVar4 = local_1cc;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar1 = local_1cc;
    pfVar4 = local_18c;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    local_214 = *(float *)(local_210 + 0x40) * *(float *)(local_20c + 0x1244);
    local_21c = *(float *)(local_210 + 0x40) * 2.0 * *(float *)(local_20c + 0x1248);
    local_1e4 = (float)local_164;
    local_1e0 = (float)local_15c;
    local_1dc = (float)local_154;
    local_1fc = (float)local_164 + local_21c * local_174;
    local_1f8 = (float)local_15c + local_21c * local_170;
    local_1f4 = (float)local_154 + local_21c * local_16c;
    puVar2 = (undefined4 *)FUN_00440130(local_2cc,local_1e4,local_1e0,local_1dc);
    local_208 = *puVar2;
    local_204 = puVar2[1];
    local_200 = puVar2[2];
    puVar2 = (undefined4 *)FUN_004462d0(local_26c,0x3f000000);
    local_14c = *puVar2;
    local_148 = puVar2[1];
    local_144 = puVar2[2];
    local_d4 = local_14c;
    local_d0 = local_148;
    local_cc = local_144;
    iVar3 = FUN_006895d0();
    if (iVar3 < 1) {
      local_220 = DAT_00920ef4;
      fVar5 = (float10)FUN_00456080();
      DAT_00920ef4 = (float)fVar5;
      local_1d8 = local_214 * local_18c[0];
      local_1d4 = local_214 * local_18c[1];
      local_1d0 = local_214 * local_18c[2];
      local_1f0 = local_214 * local_18c[3];
      local_1ec = local_214 * local_17c;
      local_1e8 = local_214 * local_178;
      fVar5 = (float10)FUN_004464c0();
      local_224 = (float)fVar5;
      local_218 = local_224 * *(float *)(local_20c + 0x1238) + *(float *)(local_20c + 0x1234);
      puVar2 = (undefined4 *)FUN_00439d00(local_284,local_1e4,local_1e0,local_1dc,local_218);
      local_134 = *puVar2;
      local_130 = puVar2[1];
      local_12c = puVar2[2];
      local_98 = local_134;
      local_94 = local_130;
      local_90 = local_12c;
      puVar2 = (undefined4 *)FUN_00439d00(local_29c,local_134,local_130,local_12c,local_218);
      local_ec = *puVar2;
      local_e8 = puVar2[1];
      local_e4 = puVar2[2];
      local_98 = local_ec;
      local_94 = local_e8;
      local_90 = local_e4;
      puVar2 = (undefined4 *)FUN_00439d00(local_2b4,local_ec,local_e8,local_e4,local_218 * -2.0);
      local_11c = *puVar2;
      local_118 = puVar2[1];
      local_114 = puVar2[2];
      local_8c = local_11c;
      local_88 = local_118;
      local_84 = local_114;
      puVar2 = (undefined4 *)FUN_00439d00(local_230,local_11c,local_118,local_114,local_218 * -2.0);
      local_bc = *puVar2;
      local_b8 = puVar2[1];
      local_b4 = puVar2[2];
      local_80 = local_bc;
      local_7c = local_b8;
      local_78 = local_b4;
      puVar2 = (undefined4 *)FUN_00439d00(local_248,local_bc,local_b8,local_b4,local_218 * 2.0);
      local_c8 = *puVar2;
      local_c4 = puVar2[1];
      local_c0 = puVar2[2];
      local_74 = local_c8;
      local_70 = local_c4;
      local_6c = local_c0;
      rand();
      FUN_0068d2f0(param_2);
      puVar2 = (undefined4 *)FUN_00440130(local_2c0,local_1e4,local_1e0,local_1dc);
      local_e0 = *puVar2;
      local_dc = puVar2[1];
      local_d8 = puVar2[2];
      local_38 = local_e0;
      local_34 = local_dc;
      local_30 = local_d8;
      puVar2 = (undefined4 *)FUN_00440130(local_260,local_1fc,local_1f8,local_1f4);
      local_f8 = *puVar2;
      local_f4 = puVar2[1];
      local_f0 = puVar2[2];
      local_2c = local_f8;
      local_28 = local_f4;
      local_24 = local_f0;
      puVar2 = (undefined4 *)FUN_004401a0(local_2a8,local_1fc,local_1f8,local_1f4);
      local_110 = *puVar2;
      local_10c = puVar2[1];
      local_108 = puVar2[2];
      local_20 = local_110;
      local_1c = local_10c;
      local_18 = local_108;
      puVar2 = (undefined4 *)FUN_004401a0(local_278,local_1e4,local_1e0,local_1dc);
      local_128 = *puVar2;
      local_124 = puVar2[1];
      local_120 = puVar2[2];
      local_14 = local_128;
      local_10 = local_124;
      local_c = local_120;
      rand();
      FUN_0068d2f0(param_2);
      puVar2 = (undefined4 *)FUN_00440130(local_2d8,local_1e4,local_1e0,local_1dc);
      local_140 = *puVar2;
      local_13c = puVar2[1];
      local_138 = puVar2[2];
      local_68 = local_140;
      local_64 = local_13c;
      local_60 = local_138;
      puVar2 = (undefined4 *)FUN_00440130(local_290,local_1fc,local_1f8,local_1f4);
      local_a4 = *puVar2;
      local_a0 = puVar2[1];
      local_9c = puVar2[2];
      local_5c = local_a4;
      local_58 = local_a0;
      local_54 = local_9c;
      puVar2 = (undefined4 *)FUN_004401a0(local_23c,local_1fc,local_1f8,local_1f4);
      local_104 = *puVar2;
      local_100 = puVar2[1];
      local_fc = puVar2[2];
      local_50 = local_104;
      local_4c = local_100;
      local_48 = local_fc;
      puVar2 = (undefined4 *)FUN_004401a0(local_254,local_1e4,local_1e0,local_1dc);
      local_b0 = *puVar2;
      local_ac = puVar2[1];
      local_a8 = puVar2[2];
      local_44 = local_b0;
      local_40 = local_ac;
      local_3c = local_a8;
      rand();
      FUN_0068d2f0(param_2);
      DAT_00920ef4 = local_220;
    }
  }
  FUN_0083e885();
  return;
}

