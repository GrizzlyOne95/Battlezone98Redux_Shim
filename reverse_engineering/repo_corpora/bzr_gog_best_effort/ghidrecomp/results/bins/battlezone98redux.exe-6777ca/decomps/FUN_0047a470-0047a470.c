
void __thiscall FUN_0047a470(int param_1,undefined4 param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  undefined1 local_2b8 [12];
  undefined1 local_2ac [12];
  undefined1 local_2a0 [24];
  undefined1 local_288 [12];
  undefined1 local_27c [12];
  undefined1 local_270 [36];
  undefined1 local_24c [12];
  undefined1 local_240 [12];
  undefined1 local_234 [12];
  undefined1 local_228 [12];
  undefined1 local_21c [12];
  undefined1 local_210 [12];
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
  local_1e8 = param_1;
  if (((0 < *(int *)(*(int *)(param_1 + 0xc) + 0x84)) &&
      (0.0 < *(float *)(*(int *)(param_1 + 0xc) + 0x78))) &&
     (0.0 < *(float *)(*(int *)(param_1 + 0xc) + 0x7c))) {
    local_204 = DAT_00920ef4;
    pfVar1 = (float *)(*(int *)(param_1 + 0x14) + 0x20);
    pfVar4 = local_a8;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    local_f0 = (float)(local_80 - *(double *)(param_1 + 0xe8));
    local_ec = (float)(local_78 - *(double *)(param_1 + 0xf0));
    local_e8 = (float)(local_70 - *(double *)(param_1 + 0xf8));
    local_1f0 = local_f0 * local_90 + local_ec * local_8c + local_e8 * local_88;
    local_80 = *(double *)(param_1 + 0xe8);
    local_78 = *(double *)(param_1 + 0xf0);
    local_70 = *(double *)(param_1 + 0xf8);
    pfVar1 = (float *)FUN_0081fe60();
    pfVar4 = local_190;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar1 = local_190;
    pfVar4 = local_a8;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar1 = (float *)FUN_00439de0();
    local_19c = *pfVar1;
    local_198 = pfVar1[1];
    local_194 = pfVar1[2];
    local_120 = local_19c;
    local_11c = local_198;
    local_118 = local_194;
    puVar2 = (undefined4 *)FUN_004795e0();
    local_1e4 = *puVar2;
    local_1e0 = puVar2[1];
    local_1dc = puVar2[2];
    puVar2 = (undefined4 *)FUN_004462d0(local_27c,*(undefined4 *)(*(int *)(local_1e8 + 0xc) + 0x78))
    ;
    local_1b4 = *puVar2;
    local_1b0 = puVar2[1];
    local_1ac = puVar2[2];
    local_108 = local_1b4;
    local_104 = local_1b0;
    local_100 = local_1ac;
    puVar2 = (undefined4 *)FUN_00439d80();
    local_1d8 = *puVar2;
    local_1d4 = puVar2[1];
    local_1d0 = puVar2[2];
    puVar2 = (undefined4 *)FUN_004462d0(local_2ac,*(undefined4 *)(*(int *)(local_1e8 + 0xc) + 0x78))
    ;
    local_1c0 = *puVar2;
    local_1bc = puVar2[1];
    local_1b8 = puVar2[2];
    local_cc = local_1c0;
    local_c8 = local_1bc;
    local_c4 = local_1b8;
    while (0.0 < local_1f0) {
      local_1a8 = local_19c;
      local_1a4 = local_198;
      local_1a0 = local_194;
      local_1ec = local_1f0;
      pfVar1 = (float *)(*(int *)(local_1e8 + 0xc) + 0x7c);
      if (local_1f0 < *pfVar1 || local_1f0 == *pfVar1) {
        local_80 = (double)(local_90 * local_1f0) + local_80;
        local_78 = (double)(local_8c * local_1f0) + local_78;
        local_70 = (double)(local_88 * local_1f0) + local_70;
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
          fVar5 = (float10)FUN_004464c0();
          local_1fc = (float)fVar5;
          local_1f8 = local_1fc * *(float *)(*(int *)(local_1e8 + 0xc) + 0x80);
          fVar5 = (float10)FUN_004464c0();
          local_200 = (float)fVar5;
          local_1f4 = local_200 * *(float *)(*(int *)(local_1e8 + 0xc) + 0x80);
          local_19c = local_a8[0] * local_1f8 + local_a8[3] * local_1f4 + local_19c;
          local_198 = local_a8[1] * local_1f8 + local_98 * local_1f4 + local_198;
          local_194 = local_a8[2] * local_1f8 + local_94 * local_1f4 + local_194;
        }
      }
      local_1f0 = local_1f0 - local_1ec;
      puVar2 = (undefined4 *)FUN_00440130(local_228,local_1a8,local_1a4,local_1a0);
      local_1cc = *puVar2;
      local_1c8 = puVar2[1];
      local_1c4 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004462d0(local_2a0,0x3f000000);
      local_150 = *puVar2;
      local_14c = puVar2[1];
      local_148 = puVar2[2];
      local_d8 = local_150;
      local_d4 = local_14c;
      local_d0 = local_148;
      iVar3 = FUN_006895d0();
      if (iVar3 < 1) {
        fVar5 = (float10)FUN_0047b6f0();
        DAT_00920ef4 = (float)fVar5;
        puVar2 = (undefined4 *)FUN_00440130(local_240,local_1a8,local_1a4,local_1a0);
        local_e4 = *puVar2;
        local_e0 = puVar2[1];
        local_dc = puVar2[2];
        local_38 = local_e4;
        local_34 = local_e0;
        local_30 = local_dc;
        puVar2 = (undefined4 *)FUN_00440130(local_288,local_19c,local_198,local_194);
        local_fc = *puVar2;
        local_f8 = puVar2[1];
        local_f4 = puVar2[2];
        local_2c = local_fc;
        local_28 = local_f8;
        local_24 = local_f4;
        puVar2 = (undefined4 *)FUN_004401a0(local_210,local_19c,local_198,local_194);
        local_114 = *puVar2;
        local_110 = puVar2[1];
        local_10c = puVar2[2];
        local_20 = local_114;
        local_1c = local_110;
        local_18 = local_10c;
        puVar2 = (undefined4 *)FUN_004401a0(local_2b8,local_1a8,local_1a4,local_1a0);
        local_12c = *puVar2;
        local_128 = puVar2[1];
        local_124 = puVar2[2];
        local_14 = local_12c;
        local_10 = local_128;
        local_c = local_124;
        FUN_0068d2f0(param_2);
        puVar2 = (undefined4 *)FUN_00440130(local_270,local_1a8,local_1a4,local_1a0);
        local_b4 = *puVar2;
        local_b0 = puVar2[1];
        local_ac = puVar2[2];
        local_68 = local_b4;
        local_64 = local_b0;
        local_60 = local_ac;
        puVar2 = (undefined4 *)FUN_00440130(local_21c,local_19c,local_198,local_194);
        local_144 = *puVar2;
        local_140 = puVar2[1];
        local_13c = puVar2[2];
        local_5c = local_144;
        local_58 = local_140;
        local_54 = local_13c;
        puVar2 = (undefined4 *)FUN_004401a0(local_234,local_19c,local_198,local_194);
        local_c0 = *puVar2;
        local_bc = puVar2[1];
        local_b8 = puVar2[2];
        local_50 = local_c0;
        local_4c = local_bc;
        local_48 = local_b8;
        puVar2 = (undefined4 *)FUN_004401a0(local_24c,local_1a8,local_1a4,local_1a0);
        local_138 = *puVar2;
        local_134 = puVar2[1];
        local_130 = puVar2[2];
        local_44 = local_138;
        local_40 = local_134;
        local_3c = local_130;
        FUN_0068d2f0(param_2);
      }
    }
    DAT_00920ef4 = local_204;
  }
  FUN_0083e885();
  return;
}

