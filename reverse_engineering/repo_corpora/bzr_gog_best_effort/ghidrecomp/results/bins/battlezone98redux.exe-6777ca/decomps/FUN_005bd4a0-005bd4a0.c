
void __thiscall FUN_005bd4a0(int param_1,undefined4 param_2)

{
  float *pfVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  undefined1 local_2b0 [12];
  undefined1 local_2a4 [12];
  undefined1 local_298 [12];
  undefined1 local_28c [12];
  undefined1 local_280 [12];
  undefined1 local_274 [12];
  undefined1 local_268 [12];
  undefined1 local_25c [12];
  undefined1 local_250 [12];
  undefined1 local_244 [12];
  undefined1 local_238 [12];
  undefined4 local_22c;
  float local_228;
  int local_224;
  int local_220;
  int local_21c;
  int local_218;
  int local_214;
  float local_210;
  float local_20c;
  int local_208;
  float local_204;
  int local_200;
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
  float local_140;
  float local_13c;
  float local_138;
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
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
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
  local_208 = *(int *)(param_1 + 0x14) + 0x20;
  local_200 = param_1;
  if ((*(uint *)(*(int *)(param_1 + 0x14) + 0x14) & 8) != 0) {
    local_228 = DAT_00920ef4;
    if ((((0 < *(int *)(*(int *)(param_1 + 0xc) + 0x80)) &&
         (0 < *(int *)(*(int *)(param_1 + 0xc) + 0x84))) &&
        (0.0 < *(float *)(*(int *)(param_1 + 0xc) + 0x78))) &&
       (0.0 < *(float *)(*(int *)(param_1 + 0xc) + 0x7c))) {
      local_20c = *(float *)(*(int *)(param_1 + 0xc) + 0x78);
      local_210 = *(float *)(*(int *)(param_1 + 0xc) + 0x7c);
      pfVar1 = (float *)FUN_0081fe60();
      pfVar5 = local_1cc;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar5 = *pfVar1;
        pfVar1 = pfVar1 + 1;
        pfVar5 = pfVar5 + 1;
      }
      pfVar1 = local_1cc;
      pfVar5 = local_18c;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar5 = *pfVar1;
        pfVar1 = pfVar1 + 1;
        pfVar5 = pfVar5 + 1;
      }
      local_b0 = -local_210 * local_174;
      local_ac = -local_210 * local_170;
      local_a8 = -local_210 * local_16c;
      local_1d8 = (float)((double)(*(float *)(*(int *)(local_200 + 0x14) + 0xb8) * local_174) +
                         local_164);
      local_1d4 = (float)((double)(*(float *)(*(int *)(local_200 + 0x14) + 0xb8) * local_170) +
                         local_15c);
      local_1d0 = (float)((double)(*(float *)(*(int *)(local_200 + 0x14) + 0xb8) * local_16c) +
                         local_154);
      local_1e4 = local_1d8 + local_b0;
      local_1e0 = local_1d4 + local_ac;
      local_1dc = local_1d0 + local_a8;
      local_140 = local_b0 * 0.5 + local_1d8;
      local_13c = local_ac * 0.5 + local_1d4;
      local_138 = local_a8 * 0.5 + local_1d0;
      iVar4 = FUN_006895d0();
      if (iVar4 < 1) {
        iVar4 = *(int *)(local_200 + 0xc);
        iVar2 = rand();
        local_214 = iVar2 % *(int *)(*(int *)(local_200 + 0xc) + 0x84) + *(int *)(iVar4 + 0x80);
        local_1f0 = local_20c * local_18c[0];
        local_1ec = local_20c * local_18c[1];
        local_1e8 = local_20c * local_18c[2];
        local_1fc = local_20c * local_18c[3];
        local_1f8 = local_20c * local_17c;
        local_1f4 = local_20c * local_178;
        fVar6 = (float10)FUN_00456080(local_1d0,local_1dc);
        DAT_00920ef4 = (float)fVar6;
        puVar3 = (undefined4 *)
                 FUN_00440130(local_2a4,local_1d8,local_1d4,local_1d0,local_1f0,local_1ec,local_1e8)
        ;
        local_104 = *puVar3;
        local_100 = puVar3[1];
        local_fc = puVar3[2];
        local_68 = local_104;
        local_64 = local_100;
        local_60 = local_fc;
        puVar3 = (undefined4 *)
                 FUN_00440130(local_268,local_1e4,local_1e0,local_1dc,local_1f0,local_1ec,local_1e8)
        ;
        local_134 = *puVar3;
        local_130 = puVar3[1];
        local_12c = puVar3[2];
        local_5c = local_134;
        local_58 = local_130;
        local_54 = local_12c;
        puVar3 = (undefined4 *)
                 FUN_004401a0(local_244,local_1e4,local_1e0,local_1dc,local_1f0,local_1ec,local_1e8)
        ;
        local_11c = *puVar3;
        local_118 = puVar3[1];
        local_114 = puVar3[2];
        local_50 = local_11c;
        local_4c = local_118;
        local_48 = local_114;
        puVar3 = (undefined4 *)
                 FUN_004401a0(local_25c,local_1d8,local_1d4,local_1d0,local_1f0,local_1ec,local_1e8)
        ;
        local_ec = *puVar3;
        local_e8 = puVar3[1];
        local_e4 = puVar3[2];
        local_44 = local_ec;
        local_40 = local_e8;
        local_3c = local_e4;
        FUN_0068d2f0(param_2,local_214,&local_68,4);
        puVar3 = (undefined4 *)
                 FUN_00440130(local_274,local_1d8,local_1d4,local_1d0,local_1fc,local_1f8,local_1f4)
        ;
        local_e0 = *puVar3;
        local_dc = puVar3[1];
        local_d8 = puVar3[2];
        local_38 = local_e0;
        local_34 = local_dc;
        local_30 = local_d8;
        puVar3 = (undefined4 *)
                 FUN_00440130(local_28c,local_1e4,local_1e0,local_1dc,local_1fc,local_1f8,local_1f4)
        ;
        local_bc = *puVar3;
        local_b8 = puVar3[1];
        local_b4 = puVar3[2];
        local_2c = local_bc;
        local_28 = local_b8;
        local_24 = local_b4;
        puVar3 = (undefined4 *)
                 FUN_004401a0(local_250,local_1e4,local_1e0,local_1dc,local_1fc,local_1f8,local_1f4)
        ;
        local_f8 = *puVar3;
        local_f4 = puVar3[1];
        local_f0 = puVar3[2];
        local_20 = local_f8;
        local_1c = local_f4;
        local_18 = local_f0;
        puVar3 = (undefined4 *)
                 FUN_004401a0(local_2b0,local_1d8,local_1d4,local_1d0,local_1fc,local_1f8,local_1f4)
        ;
        local_110 = *puVar3;
        local_10c = puVar3[1];
        local_108 = puVar3[2];
        local_14 = local_110;
        local_10 = local_10c;
        local_c = local_108;
        FUN_0068d2f0(param_2,local_214,&local_38,4);
      }
    }
    if (((0 < *(int *)(*(int *)(local_200 + 0xc) + 0x8c)) &&
        (0 < *(int *)(*(int *)(local_200 + 0xc) + 0x90))) &&
       (0.0 < *(float *)(*(int *)(local_200 + 0xc) + 0x88))) {
      local_204 = *(float *)(*(int *)(local_200 + 0xc) + 0x88);
      if (*(int *)(*(int *)(local_200 + 0x14) + 100) == 0) {
        pfVar1 = (float *)FUN_006897e0(local_298,param_2,*(undefined8 *)(local_208 + 0x28),
                                       *(undefined8 *)(local_208 + 0x30),
                                       *(undefined8 *)(local_208 + 0x38));
        local_d4 = *pfVar1;
        local_d0 = pfVar1[1];
        local_cc = pfVar1[2];
        local_a4 = local_d4;
        local_a0 = local_d0;
        local_9c = local_cc;
      }
      else {
        pfVar1 = (float *)FUN_006897e0(local_238,param_2,
                                       (double)((*(float *)(*(int *)(local_200 + 0x14) + 0xb8) -
                                                0.05) * *(float *)(local_208 + 0x18)) +
                                       *(double *)(local_208 + 0x28),
                                       (double)((*(float *)(*(int *)(local_200 + 0x14) + 0xb8) -
                                                0.05) * *(float *)(local_208 + 0x1c)) +
                                       *(double *)(local_208 + 0x30),
                                       (double)((*(float *)(*(int *)(local_200 + 0x14) + 0xb8) -
                                                0.05) * *(float *)(local_208 + 0x20)) +
                                       *(double *)(local_208 + 0x38));
        local_c8 = *pfVar1;
        local_c4 = pfVar1[1];
        local_c0 = pfVar1[2];
        local_a4 = local_c8;
        local_a0 = local_c4;
        local_9c = local_c0;
      }
      iVar4 = FUN_006895d0();
      if (iVar4 < 1) {
        iVar4 = *(int *)(local_200 + 0xc);
        iVar2 = rand();
        local_21c = iVar2 % *(int *)(*(int *)(local_200 + 0xc) + 0x90) + *(int *)(iVar4 + 0x8c);
        DAT_00920ef4 = local_9c - local_204;
        local_98 = local_a4 - local_204;
        local_94 = local_a0 + local_204;
        local_90 = local_9c;
        local_8c = local_a4 + local_204;
        local_88 = local_a0 + local_204;
        local_84 = local_9c;
        local_80 = local_a4 + local_204;
        local_7c = local_a0 - local_204;
        local_78 = local_9c;
        local_74 = local_a4 - local_204;
        local_70 = local_a0 - local_204;
        local_6c = local_9c;
        FUN_0068d2f0(param_2,local_21c,&local_98,4);
      }
    }
    if (0 < *(int *)(*(int *)(local_200 + 0xc) + 0xb8)) {
      local_218 = *(int *)(local_200 + 0xc);
      if (((-1 < *(int *)(local_218 + 0xc4)) &&
          ((0 < *(int *)(local_218 + 0xc4) || (*(int *)(local_218 + 0xc0) != 0)))) &&
         (0.0 < *(float *)(*(int *)(local_200 + 0xc) + 0xb4))) {
        puVar3 = (undefined4 *)FUN_00439de0(local_280,*(int *)(local_200 + 0x14) + 0x20);
        local_14c = *puVar3;
        local_148 = puVar3[1];
        local_144 = puVar3[2];
        local_22c = *(undefined4 *)(*(int *)(local_200 + 0xc) + 0xb4);
        iVar4 = *(int *)(*(int *)(local_200 + 0xc) + 0xb8);
        local_128 = local_14c;
        local_124 = local_148;
        local_120 = local_144;
        iVar2 = rand();
        local_220 = iVar4 >> 0x1f;
        local_224 = __allrem(iVar2,iVar2 >> 0x1f,*(undefined4 *)(*(int *)(local_200 + 0xc) + 0xc0),
                             *(undefined4 *)(*(int *)(local_200 + 0xc) + 0xc4));
        local_224 = iVar4 + local_224;
        FUN_0068e600();
      }
    }
    DAT_00920ef4 = local_228;
  }
  FUN_0083e885();
  return;
}

