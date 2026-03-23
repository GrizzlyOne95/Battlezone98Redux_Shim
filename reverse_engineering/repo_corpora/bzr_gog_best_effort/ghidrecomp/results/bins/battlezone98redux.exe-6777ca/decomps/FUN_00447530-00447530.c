
void FUN_00447530(int param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_1ec [12];
  undefined1 local_1e0 [24];
  undefined1 local_1c8 [12];
  undefined1 local_1bc [12];
  void *local_1b0;
  void *local_1ac;
  float local_1a8;
  float local_1a4;
  void *local_1a0;
  void *local_19c;
  float local_198;
  float local_194;
  undefined4 *local_190;
  void *local_18c;
  undefined4 *local_188;
  float local_184;
  undefined4 *local_180;
  undefined4 *local_17c;
  void *local_178;
  void *local_174;
  float local_170;
  undefined4 *local_16c;
  int local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140 [16];
  undefined4 local_100 [16];
  undefined4 local_c0 [16];
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
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00439de0();
  local_164 = *puVar1;
  local_160 = puVar1[1];
  local_15c = puVar1[2];
  puVar1 = (undefined4 *)FUN_004401a0(local_1c8,local_164,local_160,local_15c);
  local_14c = *puVar1;
  local_148 = puVar1[1];
  local_144 = puVar1[2];
  local_50 = local_14c;
  local_4c = local_148;
  local_48 = local_144;
  fVar5 = (float10)FUN_004428b0();
  local_170 = (float)fVar5;
  if (0.0001 <= local_170) {
    fVar5 = (float10)FUN_00820570();
    local_1a4 = (float)fVar5;
    local_170 = local_1a4 * local_170;
    *(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) + local_170;
    local_194 = local_1a4;
    if (*(float *)(param_1 + 0x80) < *(float *)(local_168 + 0x17c)) {
      if (*(int *)(param_1 + 0x74) != 0) {
        local_180 = *(undefined4 **)(*(int *)(param_1 + 0x70) + -4 + *(int *)(param_1 + 0x74) * 4);
        puVar1 = (undefined4 *)FUN_00439de0();
        local_74 = *puVar1;
        local_70 = puVar1[1];
        local_6c = puVar1[2];
        local_5c = local_74;
        local_58 = local_70;
        local_54 = local_6c;
        puVar1 = (undefined4 *)FUN_0081fa10();
        puVar4 = local_c0;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar4 = puVar4 + 1;
        }
        puVar1 = local_c0;
        puVar4 = local_180;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar4 = puVar4 + 1;
        }
        local_180[0x10] =
             *(float *)(local_168 + 0x18c) * *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x7c)
        ;
      }
    }
    else {
      puVar1 = (undefined4 *)FUN_004462d0(local_1bc,*(float *)(local_168 + 0x17c) / local_170);
      local_158 = *puVar1;
      local_154 = puVar1[1];
      local_150 = puVar1[2];
      local_44 = local_158;
      local_40 = local_154;
      local_3c = local_150;
      if (1 < *(uint *)(param_1 + 0x74)) {
        local_19c = *(void **)(*(int *)(param_1 + 0x70) + -4 + *(int *)(param_1 + 0x74) * 4);
        operator_delete(local_19c);
        *(undefined4 *)(*(int *)(param_1 + 0x70) + -4 + *(int *)(param_1 + 0x74) * 4) = 0;
        *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + -1;
      }
      do {
        if (0x1ff < *(uint *)(param_1 + 0x74)) {
          FUN_007d6a70();
          break;
        }
        *(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) - *(float *)(local_168 + 0x17c);
        puVar1 = (undefined4 *)
                 FUN_00440130(local_1ec,*(undefined4 *)(param_1 + 0x84),
                              *(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 0x8c));
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        *(undefined4 *)(param_1 + 0x84) = local_38;
        *(undefined4 *)(param_1 + 0x88) = local_34;
        *(undefined4 *)(param_1 + 0x8c) = local_30;
        *(float *)(param_1 + 0x7c) =
             *(float *)(local_168 + 0x18c) * *(float *)(local_168 + 0x17c) +
             *(float *)(param_1 + 0x7c);
        local_188 = operator_new(0x48);
        local_16c = local_188;
        puVar1 = (undefined4 *)FUN_0081fa10();
        puVar4 = local_100;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar4 = puVar4 + 1;
        }
        puVar1 = local_100;
        puVar4 = local_16c;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar4 = puVar4 + 1;
        }
        local_16c[0x10] = *(undefined4 *)(param_1 + 0x7c);
        fVar5 = (float10)FUN_004464c0();
        local_184 = (float)fVar5;
        local_14 = local_184 * *(float *)(local_168 + 0x180);
        fVar5 = (float10)FUN_004464c0();
        local_198 = (float)fVar5;
        local_10 = local_198 * *(float *)(local_168 + 0x184);
        fVar5 = (float10)FUN_004464c0();
        local_1a8 = (float)fVar5;
        local_c = local_1a8 * *(float *)(local_168 + 0x188);
        pfVar2 = (float *)FUN_00440210();
        local_20 = *pfVar2;
        local_1c = pfVar2[1];
        local_18 = pfVar2[2];
        *(double *)(local_16c + 10) = (double)local_20 + *(double *)(local_16c + 10);
        *(double *)(local_16c + 0xc) = (double)local_1c + *(double *)(local_16c + 0xc);
        *(double *)(local_16c + 0xe) = (double)local_18 + *(double *)(local_16c + 0xe);
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        if (*(uint *)(param_1 + 0x78) <= *(uint *)(param_1 + 0x74)) {
          *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) << 1;
          local_1b0 = (void *)FUN_0083d92c();
          local_174 = local_1b0;
          memset(local_1b0,0,*(int *)(param_1 + 0x78) << 2);
          memcpy(local_174,*(void **)(param_1 + 0x70),*(int *)(param_1 + 0x74) << 2);
          local_18c = *(void **)(param_1 + 0x70);
          operator_delete__(local_18c);
          *(void **)(param_1 + 0x70) = local_174;
        }
        *(undefined4 **)(*(int *)(param_1 + 0x70) + *(int *)(param_1 + 0x74) * 4) = local_16c;
        *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + 1;
        if (0x1ff < *(uint *)(param_1 + 0x74)) {
          FUN_007d6a70();
          break;
        }
      } while (*(float *)(local_168 + 0x17c) <= *(float *)(param_1 + 0x80));
      if (0.0001 < *(float *)(param_1 + 0x80)) {
        if (*(uint *)(param_1 + 0x74) < 0x201) {
          puVar1 = (undefined4 *)FUN_004462d0(local_1e0,*(float *)(param_1 + 0x80) / local_170);
          local_158 = *puVar1;
          local_154 = puVar1[1];
          local_150 = puVar1[2];
          local_2c = local_158;
          local_28 = local_154;
          local_24 = local_150;
          local_190 = operator_new(0x48);
          local_17c = local_190;
          puVar1 = (undefined4 *)FUN_00439de0();
          local_80 = *puVar1;
          local_7c = puVar1[1];
          local_78 = puVar1[2];
          local_68 = local_80;
          local_64 = local_7c;
          local_60 = local_78;
          puVar1 = (undefined4 *)FUN_0081fa10();
          puVar4 = local_140;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = *puVar1;
            puVar1 = puVar1 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar1 = local_140;
          puVar4 = local_17c;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = *puVar1;
            puVar1 = puVar1 + 1;
            puVar4 = puVar4 + 1;
          }
          local_17c[0x10] =
               *(float *)(local_168 + 0x18c) * *(float *)(param_1 + 0x80) +
               *(float *)(param_1 + 0x7c);
          if (*(uint *)(param_1 + 0x78) <= *(uint *)(param_1 + 0x74)) {
            *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) << 1;
            local_1ac = (void *)FUN_0083d92c();
            local_178 = local_1ac;
            memset(local_1ac,0,*(int *)(param_1 + 0x78) << 2);
            memcpy(local_178,*(void **)(param_1 + 0x70),*(int *)(param_1 + 0x74) << 2);
            local_1a0 = *(void **)(param_1 + 0x70);
            operator_delete__(local_1a0);
            *(void **)(param_1 + 0x70) = local_178;
          }
          *(undefined4 **)(*(int *)(param_1 + 0x70) + *(int *)(param_1 + 0x74) * 4) = local_17c;
          *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + 1;
        }
        else {
          FUN_007d6a70();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

