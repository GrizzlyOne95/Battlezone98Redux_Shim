
void __thiscall FUN_0047ce80(int param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  undefined4 *puVar3;
  uint uVar4;
  float *pfVar5;
  float10 fVar6;
  undefined1 local_2c8 [12];
  undefined1 local_2bc [12];
  undefined1 local_2b0 [36];
  undefined1 local_28c [12];
  undefined1 local_280 [24];
  undefined1 local_268 [12];
  undefined1 local_25c [12];
  undefined1 local_250 [12];
  undefined1 local_244 [12];
  undefined1 local_238 [12];
  undefined1 local_22c [12];
  undefined1 local_220 [12];
  float local_214;
  uint local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  int local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190 [16];
  undefined4 local_150;
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
  float local_120;
  float local_11c;
  float local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
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
  float local_a8 [4];
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  double local_80;
  double local_78;
  double local_70;
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
  local_208 = *(float *)(param_1 + 0x78);
  local_1e8 = param_1;
  iVar1 = FUN_00439e60();
  if (param_2 == iVar1) {
    iVar1 = FUN_00451de0();
    if (iVar1 == 0) {
      fVar6 = (float10)FUN_00822d60();
      local_214 = (float)fVar6;
      *(float *)(local_1e8 + 0x78) = *(float *)(local_1e8 + 0x78) - local_214;
    }
    if (*(float *)(local_1e8 + 0x78) <= 0.0) {
      *(uint *)(*(int *)(local_1e8 + 0x14) + 0x14) =
           *(uint *)(*(int *)(local_1e8 + 0x14) + 0x14) | 0x200;
    }
  }
  if (((0 < *(int *)(*(int *)(local_1e8 + 0xc) + 0x84)) &&
      (0.0 < *(float *)(*(int *)(local_1e8 + 0xc) + 0x78))) &&
     (0.0 < *(float *)(*(int *)(local_1e8 + 0xc) + 0x7c))) {
    local_200 = DAT_00920ef4;
    pfVar2 = (float *)(*(int *)(local_1e8 + 0x14) + 0x20);
    pfVar5 = local_a8;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar5 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar5 = pfVar5 + 1;
    }
    local_f0 = (float)(local_80 - *(double *)(local_1e8 + 0xe8));
    local_ec = (float)(local_78 - *(double *)(local_1e8 + 0xf0));
    local_e8 = (float)(local_70 - *(double *)(local_1e8 + 0xf8));
    local_1f4 = local_f0 * local_90 + local_ec * local_8c + local_e8 * local_88;
    local_80 = *(double *)(local_1e8 + 0xe8);
    local_78 = *(double *)(local_1e8 + 0xf0);
    local_70 = *(double *)(local_1e8 + 0xf8);
    pfVar2 = (float *)FUN_0081fe60();
    pfVar5 = local_190;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar5 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar5 = pfVar5 + 1;
    }
    pfVar2 = local_190;
    pfVar5 = local_a8;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar5 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar5 = pfVar5 + 1;
    }
    pfVar2 = (float *)FUN_00439de0();
    local_19c = *pfVar2;
    local_198 = pfVar2[1];
    local_194 = pfVar2[2];
    local_1f0 = *(float *)(*(int *)(local_1e8 + 0xc) + 0x78);
    if (0.0 < *(float *)(*(int *)(local_1e8 + 0xc) + 0x88)) {
      local_1f0 = (local_208 / *(float *)(*(int *)(local_1e8 + 0xc) + 0x88)) * local_1f0;
    }
    local_120 = local_19c;
    local_11c = local_198;
    local_118 = local_194;
    puVar3 = (undefined4 *)FUN_004795e0();
    local_1d8 = *puVar3;
    local_1d4 = puVar3[1];
    local_1d0 = puVar3[2];
    puVar3 = (undefined4 *)FUN_004462d0(local_28c,local_1f0);
    local_1b4 = *puVar3;
    local_1b0 = puVar3[1];
    local_1ac = puVar3[2];
    local_108 = local_1b4;
    local_104 = local_1b0;
    local_100 = local_1ac;
    puVar3 = (undefined4 *)FUN_00439d80();
    local_1e4 = *puVar3;
    local_1e0 = puVar3[1];
    local_1dc = puVar3[2];
    puVar3 = (undefined4 *)FUN_004462d0(local_2bc,local_1f0);
    local_1c0 = *puVar3;
    local_1bc = puVar3[1];
    local_1b8 = puVar3[2];
    local_210 = DAT_00946734;
    local_cc = local_1c0;
    local_c8 = local_1bc;
    local_c4 = local_1b8;
    if (0.0 < *(float *)(*(int *)(local_1e8 + 0xc) + 0x80)) {
      uVar4 = (uint)*(ushort *)(local_1e8 + 0x7e) << 0xd ^ (uint)*(ushort *)(local_1e8 + 0x7e);
      uVar4 = (int)uVar4 >> 0x11 ^ uVar4;
      DAT_00946734 = (uVar4 << 5 ^ uVar4) & 0xff;
    }
    while (0.0 < local_1f4) {
      local_1a8 = local_19c;
      local_1a4 = local_198;
      local_1a0 = local_194;
      local_1ec = local_1f4;
      pfVar2 = (float *)(*(int *)(local_1e8 + 0xc) + 0x7c);
      if (local_1f4 < *pfVar2 || local_1f4 == *pfVar2) {
        local_80 = (double)(local_90 * local_1f4) + local_80;
        local_78 = (double)(local_8c * local_1f4) + local_78;
        local_70 = (double)(local_88 * local_1f4) + local_70;
        local_19c = (float)local_80;
        local_198 = (float)local_78;
        local_194 = (float)local_70;
      }
      else {
        local_1ec = *(float *)(*(int *)(local_1e8 + 0xc) + 0x7c);
        local_80 = (double)(local_90 * local_1ec) + local_80;
        local_78 = (double)(local_8c * local_1ec) + local_78;
        local_70 = (double)(local_88 * local_1ec) + local_70;
        local_19c = (float)local_80;
        local_198 = (float)local_78;
        local_194 = (float)local_70;
        if (0.0 < *(float *)(*(int *)(local_1e8 + 0xc) + 0x80)) {
          fVar6 = (float10)FUN_004464c0();
          local_204 = (float)fVar6;
          local_1f8 = local_204 * *(float *)(*(int *)(local_1e8 + 0xc) + 0x80);
          fVar6 = (float10)FUN_004464c0();
          local_20c = (float)fVar6;
          local_1fc = local_20c * *(float *)(*(int *)(local_1e8 + 0xc) + 0x80);
          local_19c = local_a8[0] * local_1f8 + local_a8[3] * local_1fc + local_19c;
          local_198 = local_a8[1] * local_1f8 + local_98 * local_1fc + local_198;
          local_194 = local_a8[2] * local_1f8 + local_94 * local_1fc + local_194;
        }
      }
      local_1f4 = local_1f4 - local_1ec;
      puVar3 = (undefined4 *)FUN_00440130(local_238,local_1a8,local_1a4,local_1a0);
      local_1cc = *puVar3;
      local_1c8 = puVar3[1];
      local_1c4 = puVar3[2];
      puVar3 = (undefined4 *)FUN_004462d0(local_2b0,0x3f000000);
      local_150 = *puVar3;
      local_14c = puVar3[1];
      local_148 = puVar3[2];
      local_d8 = local_150;
      local_d4 = local_14c;
      local_d0 = local_148;
      iVar1 = FUN_006895d0();
      if (iVar1 < 1) {
        fVar6 = (float10)FUN_0047b6f0();
        DAT_00920ef4 = (float)fVar6;
        puVar3 = (undefined4 *)FUN_00440130(local_250,local_1a8,local_1a4,local_1a0);
        local_e4 = *puVar3;
        local_e0 = puVar3[1];
        local_dc = puVar3[2];
        local_38 = local_e4;
        local_34 = local_e0;
        local_30 = local_dc;
        puVar3 = (undefined4 *)FUN_00440130(local_220,local_19c,local_198,local_194);
        local_fc = *puVar3;
        local_f8 = puVar3[1];
        local_f4 = puVar3[2];
        local_2c = local_fc;
        local_28 = local_f8;
        local_24 = local_f4;
        puVar3 = (undefined4 *)FUN_004401a0(local_268,local_19c,local_198,local_194);
        local_b4 = *puVar3;
        local_b0 = puVar3[1];
        local_ac = puVar3[2];
        local_20 = local_b4;
        local_1c = local_b0;
        local_18 = local_ac;
        puVar3 = (undefined4 *)FUN_004401a0(local_2c8,local_1a8,local_1a4,local_1a0);
        local_114 = *puVar3;
        local_110 = puVar3[1];
        local_10c = puVar3[2];
        local_14 = local_114;
        local_10 = local_110;
        local_c = local_10c;
        FUN_0068d2f0(param_2);
        puVar3 = (undefined4 *)FUN_00440130(local_280,local_1a8,local_1a4,local_1a0);
        local_c0 = *puVar3;
        local_bc = puVar3[1];
        local_b8 = puVar3[2];
        local_68 = local_c0;
        local_64 = local_bc;
        local_60 = local_b8;
        puVar3 = (undefined4 *)FUN_00440130(local_22c,local_19c,local_198,local_194);
        local_12c = *puVar3;
        local_128 = puVar3[1];
        local_124 = puVar3[2];
        local_5c = local_12c;
        local_58 = local_128;
        local_54 = local_124;
        puVar3 = (undefined4 *)FUN_004401a0(local_244,local_19c,local_198,local_194);
        local_144 = *puVar3;
        local_140 = puVar3[1];
        local_13c = puVar3[2];
        local_50 = local_144;
        local_4c = local_140;
        local_48 = local_13c;
        puVar3 = (undefined4 *)FUN_004401a0(local_25c,local_1a8,local_1a4,local_1a0);
        local_138 = *puVar3;
        local_134 = puVar3[1];
        local_130 = puVar3[2];
        local_44 = local_138;
        local_40 = local_134;
        local_3c = local_130;
        FUN_0068d2f0(param_2);
      }
    }
    DAT_00946734 = local_210;
    DAT_00920ef4 = local_200;
  }
  FUN_0083e885();
  return;
}

