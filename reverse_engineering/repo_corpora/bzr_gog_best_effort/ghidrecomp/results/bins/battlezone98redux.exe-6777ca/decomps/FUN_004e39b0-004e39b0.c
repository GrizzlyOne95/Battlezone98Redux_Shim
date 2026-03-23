
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004e39b0(int *param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_13c [12];
  undefined1 local_130 [12];
  undefined1 local_124 [12];
  undefined1 local_118 [12];
  undefined1 local_10c [12];
  double local_100;
  float local_f8;
  int *local_f4;
  int local_f0;
  int *local_ec;
  int *local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int *local_d8;
  float local_d4;
  int local_d0;
  int local_cc;
  float *local_c8;
  int *local_c4;
  int *local_c0;
  int *local_bc;
  uint local_b8;
  int *local_b4;
  char local_ad;
  int local_ac;
  undefined4 *local_a8;
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
  int local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_e4 = 0;
  local_c0 = param_1;
  if (*param_1 == 0x2e47454f) {
    local_f4 = param_1 + 9;
    local_e8 = local_f4 + param_1[6] * 3;
    local_ec = local_e8 + param_1[6] * 3;
    local_dc = 0;
    local_bc = local_ec;
    for (local_ac = 0; local_ac < param_1[7]; local_ac = local_ac + 1) {
      local_dc = local_dc + local_bc[1];
      local_bc = (int *)((int)local_bc + local_bc[1] * 0x10 + 0x37);
    }
    local_a8 = (undefined4 *)FUN_004e46e0(param_1[7],param_1[6],local_dc);
    if (local_a8 != (undefined4 *)0x0) {
      *local_a8 = 0;
      local_a8[1] = local_c0[6];
      local_a8[2] = local_c0[6];
      local_a8[3] = local_a8 + 6;
      local_a8[4] = local_a8 + local_a8[1] * 3 + 6;
      local_a8[5] = local_a8[1] * 0xc + local_a8[4];
      local_ad = '\0';
      for (local_ac = 0; local_ac < local_c0[6]; local_ac = local_ac + 1) {
        local_c8 = (float *)(local_f4 + local_ac * 3);
        *(float *)(local_a8[3] + local_ac * 0xc) = *local_c8 + _DAT_00917b10;
        *(float *)(local_a8[3] + 4 + local_ac * 0xc) = local_c8[1] + _DAT_00917b08;
        *(float *)(local_a8[3] + 8 + local_ac * 0xc) = local_c8[2] + _DAT_00917b0c;
        cVar1 = FUN_004af020(*(undefined4 *)(local_a8[3] + local_ac * 0xc));
        if (((cVar1 != '\0') ||
            (cVar1 = FUN_004af020(*(undefined4 *)(local_a8[3] + 4 + local_ac * 0xc)), cVar1 != '\0')
            ) || (cVar1 = FUN_004af020(*(undefined4 *)(local_a8[3] + 8 + local_ac * 0xc)),
                 cVar1 != '\0')) {
          *(undefined4 *)(local_a8[3] + 8 + local_ac * 0xc) = 0;
          *(undefined4 *)(local_a8[3] + 4 + local_ac * 0xc) = 0;
          *(undefined4 *)(local_a8[3] + local_ac * 0xc) = 0;
          if (local_ad == '\0') {
            FUN_007d6b70("repaired geom \"%.16s\" vertices:",local_c0 + 2);
            local_ad = '\x01';
          }
          FUN_007d6b70(&DAT_0087a470,local_ac);
        }
      }
      if (local_ad != '\0') {
        FUN_007d6b70(&DAT_0087a44c);
      }
      for (local_ac = 0; local_ac < local_c0[6]; local_ac = local_ac + 1) {
        local_c8 = (float *)(local_e8 + local_ac * 3);
        *(float *)(local_a8[4] + local_ac * 0xc) = *local_c8 + _DAT_00917b10;
        *(float *)(local_a8[4] + 4 + local_ac * 0xc) = local_c8[1] + _DAT_00917b08;
        *(float *)(local_a8[4] + 8 + local_ac * 0xc) = local_c8[2] + _DAT_00917b0c;
        cVar1 = FUN_004af020(*(undefined4 *)(local_a8[4] + local_ac * 0xc));
        if (((cVar1 != '\0') ||
            (cVar1 = FUN_004af020(*(undefined4 *)(local_a8[4] + 4 + local_ac * 0xc)), cVar1 != '\0')
            ) || (cVar1 = FUN_004af020(*(undefined4 *)(local_a8[4] + 8 + local_ac * 0xc)),
                 cVar1 != '\0')) {
          *(undefined4 *)(local_a8[4] + 8 + local_ac * 0xc) = 0;
          *(undefined4 *)(local_a8[4] + 4 + local_ac * 0xc) = 0;
          *(undefined4 *)(local_a8[4] + local_ac * 0xc) = 0;
          local_e4 = 1;
        }
      }
      local_bc = local_ec;
      local_b4 = (int *)local_a8[5];
      local_d8 = (int *)0x0;
      local_ad = '\0';
      for (local_ac = 0; local_ac < local_c0[7]; local_ac = local_ac + 1) {
        local_b4[1] = local_bc[1];
        *(char *)((int)local_b4 + 9) = (char)local_bc[2];
        *(undefined1 *)((int)local_b4 + 10) = *(undefined1 *)((int)local_bc + 9);
        *(undefined1 *)((int)local_b4 + 0xb) = *(undefined1 *)((int)local_bc + 10);
        *(undefined1 *)(local_b4 + 2) = 0;
        *(undefined1 *)(local_b4 + 7) = *(undefined1 *)((int)local_bc + 0x1f);
        *(char *)((int)local_b4 + 0x1d) = (char)local_bc[8];
        *(undefined1 *)((int)local_b4 + 0x1e) = *(undefined1 *)((int)local_bc + 0x21);
        strncpy((char *)(local_b4 + 8),(char *)((int)local_bc + 0x22),0xf);
        _strlwr((char *)(local_b4 + 8));
        if (local_d8 != (int *)0x0) {
          local_d8[0xc] = (int)local_b4;
        }
        local_b4[0xc] = 0;
        local_c4 = local_b4 + 0x10;
        local_d0 = (int)local_bc + 0x37;
        local_14 = 0.0;
        local_10 = 0.0;
        local_c = 0.0;
        local_f0 = local_b4[1];
        local_100 = (double)local_f0 + (double)(&DAT_008a2fd0)[-(local_f0 >> 0x1f)];
        local_d4 = 1.0 / (float)local_100;
        for (local_b8 = 0; local_b8 < (uint)local_b4[1]; local_b8 = local_b8 + 1) {
          local_c4[local_b8 * 4] = *(int *)(local_d0 + local_b8 * 0x10);
          local_b4[local_b8 * 4 + 0x11] = *(int *)((int)local_bc + local_b8 * 0x10 + 0x3b);
          local_b4[local_b8 * 4 + 0x12] = *(int *)((int)local_bc + local_b8 * 0x10 + 0x3f);
          local_b4[local_b8 * 4 + 0x13] = *(int *)((int)local_bc + local_b8 * 0x10 + 0x43);
          local_e0 = local_c4[local_b8 * 4];
          local_14 = local_14 + *(float *)(local_a8[3] + local_e0 * 0xc);
          local_10 = local_10 + *(float *)(local_a8[3] + 4 + local_e0 * 0xc);
          local_c = local_c + *(float *)(local_a8[3] + 8 + local_e0 * 0xc);
        }
        local_b4[0xd] = (int)(local_d4 * local_14);
        local_b4[0xe] = (int)(local_d4 * local_10);
        local_b4[0xf] = (int)(local_d4 * local_c);
        local_74 = 0;
        local_70 = 0;
        local_6c = 0;
        puVar3 = (undefined4 *)(local_a8[3] + *local_c4 * 0xc);
        local_80 = *puVar3;
        local_7c = puVar3[1];
        local_78 = puVar3[2];
        for (local_b8 = 2; local_b8 < (uint)local_b4[1]; local_b8 = local_b8 + 1) {
          puVar3 = (undefined4 *)(local_a8[3] + local_c4[(local_b8 - 1) * 4] * 0xc);
          local_8c = *puVar3;
          local_88 = puVar3[1];
          local_84 = puVar3[2];
          puVar3 = (undefined4 *)(local_a8[3] + local_c4[local_b8 * 4] * 0xc);
          local_98 = *puVar3;
          local_94 = puVar3[1];
          local_90 = puVar3[2];
          puVar3 = (undefined4 *)
                   FUN_004401a0(local_10c,local_8c,local_88,local_84,local_80,local_7c,local_78);
          local_5c = *puVar3;
          local_58 = puVar3[1];
          local_54 = puVar3[2];
          local_20 = local_5c;
          local_1c = local_58;
          local_18 = local_54;
          puVar3 = (undefined4 *)
                   FUN_004401a0(local_130,local_98,local_94,local_90,local_80,local_7c,local_78);
          local_68 = *puVar3;
          local_64 = puVar3[1];
          local_60 = puVar3[2];
          local_2c = local_68;
          local_28 = local_64;
          local_24 = local_60;
          puVar3 = (undefined4 *)FUN_004440d0(local_118,&local_5c,&local_68);
          local_a4 = *puVar3;
          local_a0 = puVar3[1];
          local_9c = puVar3[2];
          local_38 = local_a4;
          local_34 = local_a0;
          local_30 = local_9c;
          puVar3 = (undefined4 *)
                   FUN_00440130(local_124,local_74,local_70,local_6c,local_a4,local_a0,local_9c);
          local_74 = *puVar3;
          local_70 = puVar3[1];
          local_6c = puVar3[2];
          local_50 = local_74;
          local_4c = local_70;
          local_48 = local_6c;
        }
        piVar2 = (int *)FUN_004621a0(local_13c,&local_74);
        local_44 = *piVar2;
        local_40 = piVar2[1];
        local_3c = piVar2[2];
        local_b4[3] = local_44;
        local_b4[4] = local_40;
        local_b4[5] = local_3c;
        fVar4 = (float10)FUN_004428b0(local_b4 + 3,local_b4 + 0xd);
        local_f8 = (float)fVar4;
        local_b4[6] = (int)-local_f8;
        if (local_e4 != 0) {
          for (local_b8 = 0; local_b8 < (uint)local_b4[1]; local_b8 = local_b8 + 1) {
            local_cc = local_c4[local_b8 * 4];
            if (((*(float *)(local_a8[4] + local_cc * 0xc) == 0.0) &&
                (*(float *)(local_a8[4] + 4 + local_cc * 0xc) == 0.0)) &&
               (*(float *)(local_a8[4] + 8 + local_cc * 0xc) == 0.0)) {
              piVar2 = (int *)(local_a8[4] + local_cc * 0xc);
              *piVar2 = local_b4[3];
              piVar2[1] = local_b4[4];
              piVar2[2] = local_b4[5];
              if (local_ad == '\0') {
                FUN_007d6b70("repaired geom \"%.16s\" normals:",local_c0 + 2);
                local_ad = '\x01';
              }
              FUN_007d6b70(&DAT_0087a470,local_cc);
            }
          }
        }
        local_d8 = local_b4;
        local_b4 = local_c4 + local_b4[1] * 4;
        local_bc = (int *)((int)local_bc + local_bc[1] * 0x10 + 0x37);
      }
      if (local_ad != '\0') {
        FUN_007d6b70(&DAT_0087a44c);
      }
    }
  }
  FUN_0083e885();
  return;
}

