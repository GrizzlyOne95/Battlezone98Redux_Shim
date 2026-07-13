
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0050d6f0(void)

{
  undefined8 uVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  bool bVar10;
  float10 fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 local_2a8 [12];
  undefined1 local_29c [12];
  undefined1 local_290 [8];
  undefined1 local_288 [8];
  undefined4 local_280;
  undefined1 local_274 [4];
  float local_270;
  uint local_26c;
  undefined4 local_268;
  float local_264;
  undefined4 local_260;
  int local_25c;
  float local_258;
  int local_254;
  undefined4 local_250;
  float local_24c;
  int local_248;
  undefined4 local_244;
  undefined8 local_240;
  int local_238;
  float local_234;
  undefined4 local_230;
  int local_22c;
  int local_228;
  undefined4 local_224;
  int local_220;
  float local_21c;
  int *local_218;
  int local_214;
  int local_210;
  int local_20c;
  int local_208;
  float local_204;
  uint local_200;
  undefined4 local_1fc;
  uint local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  uint local_1e8;
  int local_1e4;
  undefined4 local_1e0;
  int local_1dc;
  int local_1d8;
  float local_1d4;
  int local_1d0;
  byte *local_1cc;
  int local_1c8;
  byte *local_1c4;
  int local_1c0;
  int local_1bc;
  int *local_1b8;
  undefined4 local_1b4;
  int local_1b0;
  int local_1ac;
  int local_1a8;
  int local_1a4;
  int local_1a0;
  int local_19c;
  uint local_198;
  uint local_194;
  byte local_18e;
  byte local_18d;
  uint local_18c;
  float local_188;
  char local_183;
  byte local_182;
  char local_181;
  undefined8 local_180;
  int local_178;
  int local_174;
  int local_170;
  char local_169;
  int local_168;
  uint local_164;
  int local_160;
  char local_15a;
  char local_159;
  int local_158;
  int *local_154;
  char local_14d;
  int local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  float local_13c;
  float local_138;
  float local_134;
  undefined4 local_130;
  float local_12c;
  undefined4 local_128;
  undefined4 local_118;
  float local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  float local_100;
  float local_fc;
  float local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  float local_88 [4];
  float local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  int local_58 [7];
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int local_20 [6];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_181 = FUN_0047c070();
  if ((local_181 == 'a') || (local_181 == 'b')) {
    DAT_00917f28 = DAT_00917f30;
  }
  else {
    DAT_00917f28 = DAT_00917f2c;
  }
  local_240 = FUN_00689eb0();
  local_180 = local_240;
  fVar11 = (float10)FUN_0044fb20(DAT_00917394 - DAT_0091738c,DAT_00917388 - DAT_00917390);
  local_24c = (float)fVar11;
  *(float *)(local_158 + 0xc) = ((float)local_180 * 158.0) / local_24c;
  if ((DAT_008eaab0 != 0) && (DAT_008eaaac == 0)) {
    local_1b8 = (int *)FUN_00417c70();
    if (local_1b8 != (int *)0x0) {
      local_22c = FUN_00461430();
      local_218 = (int *)FUN_00462610();
      *(int *)(local_158 + 0x28) =
           (DAT_02a13b90 * DAT_02cecee0) / 2 +
           (int)((float)(DAT_02a13b8c + _DAT_02a13b94) * (float)local_180);
      *(int *)(local_158 + 0x34) = (DAT_02cecee4 - (int)(local_180._4_4_ * 10.0)) + -1;
      *(int *)(local_158 + 0x30) = *(int *)(local_158 + 0x28) + -1 + (int)((float)local_180 * 158.0)
      ;
      *(int *)(local_158 + 0x2c) = (*(int *)(local_158 + 0x34) - (int)(local_180._4_4_ * 158.0)) + 1
      ;
      *(int *)(local_158 + 0x10) =
           (int)(((float)(*(int *)(local_158 + 0x28) + 1 + *(int *)(local_158 + 0x30)) -
                 (DAT_00917394 + DAT_0091738c) * *(float *)(local_158 + 0xc)) * 0.5);
      *(int *)(local_158 + 0x14) =
           (int)(((float)(*(int *)(local_158 + 0x2c) + 1 + *(int *)(local_158 + 0x34)) +
                 (DAT_00917388 + DAT_00917390) * *(float *)(local_158 + 0xc)) * 0.5);
      local_188 = DAT_00920ef4;
      uVar1 = local_180;
      if (DAT_00915567 == '\0') {
        iVar3 = FUN_0049f100(DAT_009175a0,DAT_009175a4,local_158 + 0x28);
        uVar1 = local_180;
        if (iVar3 != 0) {
          FUN_0050cda0();
          uVar1 = local_180;
          if (DAT_00919872 != '\0') {
            puVar4 = (undefined4 *)FUN_0050d690(local_290,DAT_009175a0,DAT_009175a4);
            FUN_005889d0(*puVar4,puVar4[1]);
            DAT_00919872 = '\0';
            uVar1 = local_180;
          }
        }
      }
      local_180._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
      local_180._0_4_ = (float)uVar1;
      local_214 = (DAT_02a13b90 * DAT_02cecee0) / 2 + (int)((float)DAT_02a13b8c * (float)local_180);
      local_210 = DAT_02cecee4 - (int)((float)_DAT_008e8bf0 * local_180._4_4_);
      local_180 = uVar1;
      iVar3 = FUN_0068f090();
      local_25c = (int)(((float)iVar3 * (float)local_180) / 2.0);
      iVar3 = FUN_0068f0c0();
      local_254 = (int)(((float)iVar3 * local_180._4_4_) / 2.0);
      DAT_00920ef4 = local_188 + 0.04;
      uVar5 = FUN_004d9b40(DAT_00917f28,local_214,local_210,local_25c,local_254,0,0);
      FUN_0068ca30(DAT_00917580,uVar5);
      DAT_00920ef4 = local_188 + 0.03;
      FUN_00687d40(local_158 + 0x20,DAT_00920ef4);
      local_e8 = (float)*(int *)(local_158 + 0x28);
      local_e4 = (float)*(int *)(local_158 + 0x2c);
      local_e0 = DAT_00920ef4;
      local_dc = 0;
      local_d8 = 0;
      local_d4 = 0x3f800000;
      local_d0 = (float)(*(int *)(local_158 + 0x30) + 1);
      local_cc = (float)*(int *)(local_158 + 0x2c);
      local_c8 = DAT_00920ef4;
      local_c4 = 0x3f800000;
      local_c0 = 0;
      local_bc = 0x3f800000;
      local_b8 = (float)(*(int *)(local_158 + 0x30) + 1);
      local_b4 = (float)(*(int *)(local_158 + 0x34) + 1);
      local_b0 = DAT_00920ef4;
      local_ac = 0x3f800000;
      local_a8 = 0x3f800000;
      local_a4 = 0x3f800000;
      local_a0 = (float)*(int *)(local_158 + 0x28);
      local_9c = (float)(*(int *)(local_158 + 0x34) + 1);
      local_98 = DAT_00920ef4;
      local_94 = 0;
      local_90 = 0x3f800000;
      local_8c = 0x3f800000;
      FUN_00686600(DAT_00917594,&local_e8,4,0xffffffff);
      FUN_006856e0();
      iVar3 = FUN_004978d0();
      if (iVar3 != 0) {
        local_13c = (float)*(double *)(DAT_00917594 + 0x58);
        local_138 = (float)*(double *)(DAT_00917594 + 0x5a);
        local_134 = (float)*(double *)(DAT_00917594 + 0x5c);
        local_88[0] = (DAT_00917594[5] - *DAT_00917594) / DAT_00917594[2];
        local_88[1] = (DAT_00917594[6] - DAT_00917594[1]) / DAT_00917594[3];
        local_88[2] = 1.0;
        local_88[3] = (DAT_00917594[7] - *DAT_00917594) / DAT_00917594[2];
        local_78 = (DAT_00917594[6] - DAT_00917594[1]) / DAT_00917594[3];
        local_74 = 0x3f800000;
        local_70 = (DAT_00917594[7] - *DAT_00917594) / DAT_00917594[2];
        local_6c = (DAT_00917594[8] - DAT_00917594[1]) / DAT_00917594[3];
        local_68 = 0x3f800000;
        local_64 = (DAT_00917594[5] - *DAT_00917594) / DAT_00917594[2];
        local_60 = (DAT_00917594[8] - DAT_00917594[1]) / DAT_00917594[3];
        local_5c = 0x3f800000;
        iVar3 = FUN_0050cdc0();
        local_264 = local_138 - *(float *)(iVar3 + 4);
        for (local_19c = 0; local_19c < 4; local_19c = local_19c + 1) {
          puVar4 = (undefined4 *)FUN_00440300(local_2a8,local_88 + local_19c * 3);
          local_130 = *puVar4;
          local_12c = (float)puVar4[1];
          local_128 = puVar4[2];
          local_118 = local_130;
          local_114 = local_12c;
          local_110 = local_128;
          puVar4 = (undefined4 *)
                   FUN_00439d00(local_29c,local_13c,local_138,local_134,-local_264 / local_12c,
                                local_130,local_12c);
          local_148 = *puVar4;
          local_144 = puVar4[1];
          local_140 = puVar4[2];
          local_10c = local_148;
          local_108 = local_144;
          local_104 = local_140;
          piVar6 = (int *)FUN_0050d630(local_288,local_148,local_144,local_140);
          iVar3 = piVar6[1];
          local_58[local_19c * 2 + 6] = *piVar6;
          local_58[local_19c * 2 + 7] = iVar3;
        }
        DAT_00920ef4 = local_188 + 0.01;
        FUN_0068af40(DAT_00917580,local_58[6],uStack_3c,uStack_38,uStack_34,DAT_0091755c,0);
        FUN_0068af40(DAT_00917580,uStack_38,uStack_34,uStack_30,uStack_2c,DAT_0091755c,0);
        FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_28,uStack_24,DAT_0091755c,0);
        FUN_0068af40(DAT_00917580,uStack_28,uStack_24,local_58[6],uStack_3c,DAT_0091755c,0);
      }
      DAT_00920ef4 = local_188;
      local_164 = DAT_00979f9c;
      local_58[0] = -1;
      local_58[1] = 0xffffffff;
      local_58[2] = 0xffffffff;
      local_58[3] = 0xffffffff;
      local_58[4] = 0xffffffff;
      local_58[5] = 0xffffffff;
      local_20[0] = DAT_009174c0;
      local_20[1] = DAT_009174c0;
      local_20[2] = DAT_009174c0;
      local_20[3] = DAT_009174c0;
      local_20[4] = DAT_009174c0;
      local_20[5] = DAT_009174c0;
      fVar11 = (float10)FUN_00822da0();
      local_234 = (float)fVar11;
      fVar11 = (float10)FUN_00822d60();
      local_270 = (float)fVar11;
      local_1f0 = DAT_00917a74;
      FUN_00422170();
      puVar4 = (undefined4 *)FID_conflict_begin();
      local_1b4 = *puVar4;
      while( true ) {
        FID_conflict_end();
        cVar2 = FID_conflict_operator__();
        if (cVar2 == '\0') break;
        puVar4 = (undefined4 *)FUN_00421ec0();
        local_154 = (int *)*puVar4;
        local_1cc = (byte *)0x87d69c;
        local_1c4 = (byte *)FUN_004978b0();
        do {
          local_18e = *local_1c4;
          bVar10 = local_18e < *local_1cc;
          if (local_18e != *local_1cc) {
LAB_0050e347:
            local_200 = -(uint)bVar10 | 1;
            goto LAB_0050e352;
          }
          if (local_18e == 0) break;
          local_18d = local_1c4[1];
          bVar10 = local_18d < local_1cc[1];
          if (local_18d != local_1cc[1]) goto LAB_0050e347;
          local_1c4 = local_1c4 + 2;
          local_1cc = local_1cc + 2;
        } while (local_18d != 0);
        local_200 = 0;
LAB_0050e352:
        local_26c = local_200;
        if (local_200 != 0) {
          local_280 = 0;
        }
        if (0.0 < (float)local_154[0x3a]) {
LAB_0050e3af:
          puVar4 = (undefined4 *)(**(code **)(local_154[6] + 0xc))();
          local_f4 = *puVar4;
          local_f0 = puVar4[1];
          local_ec = puVar4[2];
          FUN_0050d630(&local_174,local_f4,local_f0,local_ec);
          iVar3 = FUN_0049f100(local_174,local_170);
          if (iVar3 != 0) {
            local_178 = FUN_0045bba0();
            iVar3 = (**(code **)(local_154[6] + 4))();
            local_14d = iVar3 == local_22c;
            local_1e8 = (uint)(byte)local_14d;
            local_169 = FUN_0046fbf0();
            local_159 = local_154 == local_218;
            local_1f8 = (uint)(byte)local_159;
            iVar3 = (**(code **)local_154[6])();
            if (*(int *)(iVar3 + 0x1c) == 5) {
LAB_0050e549:
              local_1ec = 1;
            }
            else {
              iVar3 = (**(code **)local_154[6])();
              if (*(int *)(iVar3 + 0x1c) == 7) goto LAB_0050e549;
              iVar3 = (**(code **)local_154[6])();
              if (*(int *)(iVar3 + 0x1c) == 3) goto LAB_0050e549;
              iVar3 = (**(code **)local_154[6])();
              if (*(int *)(iVar3 + 0x1c) == 4) goto LAB_0050e549;
              local_1ec = 0;
            }
            local_182 = (byte)local_1ec;
            fVar11 = (float10)FUN_0046d040();
            local_1d4 = (float)fVar11;
            if ((local_14d == '\0') || (local_1d4 + 2.0 <= local_234)) {
              local_1f4 = 0;
            }
            else {
              local_1f4 = 1;
            }
            local_15a = (char)local_1f4;
            if (local_14d == '\0') {
LAB_0050e5df:
              local_1fc = 0;
            }
            else {
              cVar2 = FUN_00492d20();
              if (cVar2 == '\0') goto LAB_0050e5df;
              local_1fc = 1;
            }
            local_183 = (char)local_1fc;
            local_160 = -1;
            local_18c = 0xffffffff;
            local_14c = -1;
            if (local_15a == '\0') {
              if ((float)local_154[0x3a] <= 0.0) {
                iVar3 = (**(code **)(local_154[6] + 4))();
                iVar7 = FUN_00461430();
                if (iVar3 == iVar7) {
                  local_154[0x3a] = 0x3f800000;
                }
              }
              iVar3 = FUN_008445c0();
              uVar8 = FUN_00492ce0();
              local_198 = iVar3 << 0x18 | uVar8 & 0xffffff;
            }
            else {
              local_198 = DAT_0091757c;
            }
            if (((local_14d != '\0') && (local_154 != local_1b8)) && (_DAT_009173d0 < local_1d4)) {
              FUN_0043aa30("cgrowl.wav",0,0);
              _DAT_009173d0 = local_1d4 + 1.0;
            }
            local_1a8 = DAT_00979fc0 + -2;
            uVar1 = local_180;
            switch(local_1a8) {
            case 0:
              if (((local_14d != '\0') && (local_15a != '\0')) && (-1 < local_178)) {
                for (local_194 = 0; local_194 < 8; local_194 = local_194 + 1) {
                  if ((*(int *)(&DAT_008e8b20 + local_194 * 0x10) <= local_178) &&
                     (local_178 <= *(int *)(&DAT_008e8b24 + local_194 * 0x10))) {
                    local_14c = 0;
                    local_18c = local_194;
                    local_260 = *(undefined4 *)(&DAT_009173e8 + local_194 * 0x10);
                    local_1c0 = (*(int *)(&DAT_009173ec + local_194 * 0x10) +
                                *(int *)(&DAT_009173f4 + local_194 * 0x10)) / 2;
                    if (local_1c0 < local_20[0]) {
                      local_20[0] = local_1c0;
                    }
                    FUN_0068af40(DAT_00917580,local_260,local_1c0,DAT_009174bc,local_1c0,
                                 DAT_02a13b98);
                    uVar1 = local_180;
                    break;
                  }
                }
              }
              break;
            case 1:
              if (((local_14d != '\0') && (-1 < (int)local_164)) &&
                 ((local_164 < 8 &&
                  ((*(int *)(&DAT_008e8b20 + local_164 * 0x10) <= local_178 &&
                   (local_178 <= *(int *)(&DAT_008e8b24 + local_164 * 0x10))))))) {
                local_18c = local_164;
                if (*(int *)(&DAT_008e8b24 + local_164 * 0x10) !=
                    *(int *)(&DAT_008e8b20 + local_164 * 0x10)) {
                  local_160 = local_178 - *(int *)(&DAT_008e8b20 + local_164 * 0x10);
                }
                if (local_15a == '\0') {
                  if (local_160 == DAT_00979fb8) {
                    local_14c = 1;
                  }
                  else if (local_183 == '\0') {
                    cVar2 = (**(code **)(*local_154 + 0x38))();
                    if (cVar2 != '\0') {
                      cVar2 = FUN_0045bbc0();
                      if (cVar2 == '\0') {
                        local_14c = 3;
                        goto LAB_0050e9bf;
                      }
                    }
                    local_14c = 5;
                  }
                  else {
                    local_14c = 2;
                  }
                }
                else {
                  local_14c = 0;
                }
LAB_0050e9bf:
                local_250 = *(undefined4 *)(&DAT_009173e8 + local_160 * 0x10);
                local_1bc = (*(int *)(&DAT_009173ec + local_160 * 0x10) +
                            *(int *)(&DAT_009173f4 + local_160 * 0x10)) / 2;
                if (local_1bc < local_20[local_14c]) {
                  local_20[local_14c] = local_1bc;
                }
                FUN_0068af40(DAT_00917580,local_250,local_1bc,DAT_009174bc,local_1bc,
                             (&DAT_02a13b98)[local_14c]);
                uVar1 = local_180;
              }
              break;
            case 2:
              if ((((local_14d != '\0') && (-1 < (int)local_164)) && (local_164 < 8)) &&
                 ((*(int *)(&DAT_008e8b20 + local_164 * 0x10) <= local_178 &&
                  (local_178 <= *(int *)(&DAT_008e8b24 + local_164 * 0x10))))) {
                local_18c = local_164;
                if (*(int *)(&DAT_008e8b24 + local_164 * 0x10) !=
                    *(int *)(&DAT_008e8b20 + local_164 * 0x10)) {
                  local_160 = local_178 - *(int *)(&DAT_008e8b20 + local_164 * 0x10);
                }
                if (local_15a == '\0') {
                  if (local_183 != '\0') {
                    local_14c = 2;
                  }
                }
                else {
                  local_14c = 0;
                }
                if (-1 < local_14c) {
                  local_224 = DAT_008fe62c;
                  local_1c8 = (DAT_008fe630 + DAT_008fe638) / 2;
                  if (local_1c8 < local_20[local_14c]) {
                    local_20[local_14c] = local_1c8;
                  }
                  FUN_0068af40(DAT_00917580,DAT_008fe62c,local_1c8,DAT_009174bc,local_1c8,
                               (&DAT_02a13b98)[local_14c]);
                  uVar1 = local_180;
                }
              }
              break;
            case 3:
              if (((local_14d != '\0') && (-1 < (int)local_164)) &&
                 ((local_164 < 8 &&
                  ((*(int *)(&DAT_008e8b20 + local_164 * 0x10) <= local_178 &&
                   (local_178 <= *(int *)(&DAT_008e8b24 + local_164 * 0x10))))))) {
                local_18c = local_164;
                if (*(int *)(&DAT_008e8b24 + local_164 * 0x10) !=
                    *(int *)(&DAT_008e8b20 + local_164 * 0x10)) {
                  local_160 = local_178 - *(int *)(&DAT_008e8b20 + local_164 * 0x10);
                }
                if (local_15a == '\0') {
                  if (local_160 == DAT_00979fb8) {
                    local_14c = 1;
                  }
                  else if (local_159 == '\0') {
                    local_14c = 3;
                  }
                  else {
                    local_14c = 2;
                  }
                }
                else {
                  local_14c = 0;
                }
                local_268 = *(undefined4 *)(&DAT_009173e8 + local_160 * 0x10);
                local_1d0 = (*(int *)(&DAT_009173ec + local_160 * 0x10) +
                            *(int *)(&DAT_009173f4 + local_160 * 0x10)) / 2;
                if (local_1d0 < local_20[local_14c]) {
                  local_20[local_14c] = local_1d0;
                }
                FUN_0068af40(DAT_00917580,local_268,local_1d0,DAT_009174bc,local_1d0,
                             (&DAT_02a13b98)[local_14c]);
                uVar1 = local_180;
              }
              break;
            case 4:
              if (local_14d == '\0') {
                local_228 = FUN_00462380();
                for (local_1a4 = 0; local_1a4 < DAT_00979e34; local_1a4 = local_1a4 + 1) {
                  if (*(int *)(&DAT_00979e0c + local_1a4 * 4) == local_228) {
                    local_160 = local_1a4;
                    break;
                  }
                }
                if (-1 < local_160) {
                  if (local_160 == DAT_00979fb8) {
                    local_14c = 1;
                  }
                  else if (local_159 == '\0') {
                    local_14c = 4;
                  }
                  else {
                    local_14c = 2;
                  }
                  local_230 = *(undefined4 *)(&DAT_009173e8 + local_160 * 0x10);
                  local_1ac = (*(int *)(&DAT_009173ec + local_160 * 0x10) +
                              *(int *)(&DAT_009173f4 + local_160 * 0x10)) / 2;
                  if (local_1ac < local_20[local_14c]) {
                    local_20[local_14c] = local_1ac;
                  }
                  FUN_0068af40(DAT_00917580,local_230,local_1ac,DAT_009174bc,local_1ac,
                               (&DAT_02a13b98)[local_14c]);
                }
              }
            case 5:
              uVar1 = local_180;
              if (local_14d != '\0') {
                local_238 = FUN_00462380();
                for (local_1a0 = 0; local_1a0 < DAT_00979e34; local_1a0 = local_1a0 + 1) {
                  if (*(int *)(&DAT_00979e0c + local_1a0 * 4) == local_238) {
                    local_160 = local_1a0;
                    break;
                  }
                }
                uVar1 = local_180;
                if (-1 < local_160) {
                  if (local_160 == DAT_00979fb8) {
                    local_14c = 1;
                  }
                  else if (local_159 == '\0') {
                    local_14c = 3;
                  }
                  else {
                    local_14c = 2;
                  }
                  local_244 = *(undefined4 *)(&DAT_009173e8 + local_160 * 0x10);
                  local_1b0 = (*(int *)(&DAT_009173ec + local_160 * 0x10) +
                              *(int *)(&DAT_009173f4 + local_160 * 0x10)) / 2;
                  if (local_1b0 < local_20[local_14c]) {
                    local_20[local_14c] = local_1b0;
                  }
                  FUN_0068af40(DAT_00917580,local_244,local_1b0,DAT_009174bc,local_1b0,
                               (&DAT_02a13b98)[local_14c]);
                  uVar1 = local_180;
                }
              }
            }
            local_180._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
            local_180._0_4_ = (float)uVar1;
            local_180 = uVar1;
            if (local_154 == local_1b8) {
              fVar12 = local_180._4_4_ * 1.0;
              fVar13 = (float)local_180 * 1.0;
              fVar14 = local_180._4_4_ * 1.0;
              fVar15 = (float)local_180 * 1.0;
              FUN_0068afb0(DAT_00917580,local_174 - (int)fVar15,local_170 - (int)fVar14,
                           (int)fVar13 + local_174,(int)fVar12 + local_170,local_198,0);
              pfVar9 = (float *)FUN_00462490();
              local_100 = *pfVar9;
              local_fc = pfVar9[1];
              local_f8 = pfVar9[2];
              fVar11 = (float10)FUN_00820570((double)(local_100 * local_100 + local_f8 * local_f8 +
                                                     1.1754944e-38));
              local_258 = (float)fVar11;
              local_204 = local_258 * 10.0;
              local_248 = (int)(local_100 * local_204);
              local_220 = (int)(local_f8 * local_204);
              local_21c = local_258;
              FUN_0050d630(&local_20c,local_f4,local_f0,local_ec);
              FUN_0068af40(DAT_00917580,local_20c + local_248,local_208 - local_220,local_20c,
                           local_208,DAT_0091755c);
            }
            else if (local_14c < 0) {
              if (((local_15a == '\0') && (local_169 == '\0')) && (local_159 == '\0')) {
                local_1e4 = 1;
              }
              else {
                local_1e4 = 0;
              }
              DAT_00920ef4 = local_188 + 0.01 + (float)local_1e4 * 0.005 + (float)local_182 * 0.005;
              if (local_182 == 0) {
                fVar12 = local_180._4_4_ * 1.0;
                fVar13 = (float)local_180 * 1.0;
                fVar14 = local_180._4_4_ * 1.0;
                fVar15 = (float)local_180 * 1.0;
                FUN_0068afb0(DAT_00917580,local_174 - (int)fVar15,local_170 - (int)fVar14,
                             (int)fVar13 + local_174,(int)fVar12 + local_170,local_198);
                uVar1 = local_180;
              }
              else {
                DAT_00920ef4 = local_188 + 0.015;
                fVar12 = local_180._4_4_ * 0.5;
                fVar13 = (float)local_180 * 0.5;
                fVar14 = local_180._4_4_ * 0.5;
                fVar15 = (float)local_180 * 0.5;
                FUN_0068afb0(DAT_00917580,local_174 - (int)fVar15,local_170 - (int)fVar14,
                             (int)fVar13 + local_174,(int)fVar12 + local_170,local_198);
                uVar1 = local_180;
              }
              local_180._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
              if ((local_169 != '\0') || (local_159 != '\0')) {
                fVar12 = local_180._4_4_ * 3.0;
                local_180 = uVar1;
                FUN_0068aed0(DAT_00917580,local_174,local_170,(int)fVar12,local_198);
                uVar1 = local_180;
              }
              DAT_00920ef4 = local_188;
              local_180 = uVar1;
            }
            else {
              if (local_58[local_14c] < local_174) {
                local_58[local_14c] = local_174;
              }
              local_1e0 = (&DAT_02a13b98)[local_14c];
              DAT_00920ef4 = local_188 + 0.005;
              FUN_0068af40(DAT_00917580,local_174,DAT_009174c0,local_174,local_170,local_1e0);
              DAT_00920ef4 = local_188 + 0.001;
              if (local_160 < 0) {
                uVar1 = local_180;
                if (-1 < (int)local_18c) {
                  FUN_00417990();
                  FUN_0068c560(DAT_00917580,*(undefined4 *)(&DAT_008e8b2c + local_18c * 0x10),
                               local_174,local_170,0x250005);
                  uVar1 = local_180;
                }
              }
              else {
                FUN_00417990();
                FUN_0068c560(DAT_00917580,*(undefined4 *)(&DAT_008e8ba4 + local_160 * 8),local_174,
                             local_170,0x250005);
                uVar1 = local_180;
              }
              local_180._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
              if ((local_169 != '\0') || (local_159 != '\0')) {
                fVar12 = local_180._4_4_ * 6.0;
                local_180 = uVar1;
                FUN_0068aed0(DAT_00917580,local_174,local_170,(int)fVar12,local_198);
                uVar1 = local_180;
              }
              DAT_00920ef4 = local_188;
              local_180 = uVar1;
            }
          }
        }
        else {
          iVar3 = (**(code **)(local_154[6] + 4))();
          iVar7 = FUN_00461430();
          if (iVar3 == iVar7) goto LAB_0050e3af;
        }
        FUN_0046b260(local_274,0);
      }
      local_1dc = DAT_009174bc;
      for (local_168 = 0; local_168 < 6; local_168 = local_168 + 1) {
        if (local_1dc < local_58[local_168]) {
          FUN_0068af40(DAT_00917580,local_1dc,DAT_009174c0,local_58[local_168],DAT_009174c0,
                       (&DAT_02a13b98)[local_168],0);
          local_1dc = local_58[local_168];
        }
      }
      local_1d8 = DAT_009174c0;
      for (local_168 = 0; local_168 < 6; local_168 = local_168 + 1) {
        if (local_20[local_168] < local_1d8) {
          FUN_0068af40(DAT_00917580,DAT_009174bc,local_20[local_168],DAT_009174bc,local_1d8,
                       (&DAT_02a13b98)[local_168],0);
          local_1d8 = local_20[local_168];
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

