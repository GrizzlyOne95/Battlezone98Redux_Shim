
void __fastcall FUN_005dde00(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  float *pfVar5;
  undefined4 *puVar6;
  ulong uVar7;
  float *pfVar8;
  undefined4 *puVar9;
  float fVar10;
  float fVar11;
  undefined1 local_270 [64];
  undefined1 local_230 [12];
  undefined1 local_224 [12];
  undefined1 local_218 [12];
  undefined1 local_20c [12];
  undefined1 local_200 [12];
  undefined1 local_1f4 [12];
  undefined8 local_1e8;
  undefined8 local_1e0;
  int local_1d8;
  int local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  int local_1c0;
  float local_1bc;
  int local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  float local_1ac;
  int local_1a8;
  float local_1a4;
  char local_19e;
  undefined1 local_19d;
  float *local_19c;
  int local_198;
  int local_194;
  undefined4 local_190;
  float local_18c;
  undefined4 local_188;
  float local_184;
  float local_180;
  float local_17c;
  undefined4 local_178 [16];
  undefined4 local_138 [16];
  float local_f8 [4];
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  double local_d0;
  double local_c8;
  double local_c0;
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
  float local_88;
  float local_84;
  float local_80;
  double local_78;
  double local_70;
  double local_68;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_008eaab0 == 0) {
    *(undefined1 *)(param_1 + 0x1f0) = 0;
  }
  local_194 = param_1;
  if (*(char *)(param_1 + 0x1f0) != '\0') {
    local_19e = FUN_0047c070();
    if (local_19e == 'a') {
      DAT_00918368 = FUN_0068bed0("targetunderlay");
    }
    else {
      DAT_00918368 = FUN_0068bed0("stargetunderlay");
    }
    *(undefined1 *)(local_194 + 0x1f0) = 0;
    *(undefined1 *)(local_194 + 0x1f1) = 0;
    local_198 = FUN_00417c70();
    if (local_198 != 0) {
      iVar3 = FUN_00462610();
      if (*(int *)(local_194 + 8) != iVar3) {
        uVar4 = FUN_00462610();
        *(undefined4 *)(local_194 + 8) = uVar4;
        if (*(int *)(local_194 + 8) == 0) {
          local_1b0 = 0;
        }
        else {
          local_1b0 = (**(code **)(*(int *)(*(int *)(local_194 + 8) + 0x18) + 0x2c))();
        }
        *(undefined4 *)(local_194 + 0xc) = local_1b0;
        if (*(int *)(local_194 + 8) == 0) {
          local_1b4 = 0;
        }
        else {
          uVar4 = (**(code **)(*(int *)(*(int *)(local_194 + 8) + 0x18) + 0x30))(0x28);
          local_1b4 = FUN_0062e250(uVar4);
        }
        *(undefined4 *)(local_194 + 0x10) = local_1b4;
      }
      if (*(int *)(local_194 + 8) != 0) {
        *(undefined1 *)(local_194 + 0x1f1) = 1;
        FUN_00684ed0(local_194 + 0x18);
        local_18 = ((int)(DAT_02cecee0 * 3 + (DAT_02cecee0 * 3 >> 0x1f & 3U)) >> 2) + -0x2c;
        local_14 = 0x14;
        local_10 = DAT_02cecee0 + -0x14;
        local_c = ((int)(DAT_02cecee4 + (DAT_02cecee4 >> 0x1f & 3U)) >> 2) + 10;
        iVar3 = FUN_004344a0();
        if (iVar3 == 2) {
          local_1c8 = (float)DAT_02cecee0 / 2048.0;
          local_1cc = (float)DAT_02cecee4 / 1536.0;
          local_1c4 = (float)DAT_02cecee0 / 2.0;
          local_1bc = local_1c8 * 400.0;
          local_1d0 = local_1cc * 300.0;
          local_14 = -8;
          local_18 = (int)(local_1c4 - local_1bc / 2.0);
          local_10 = (int)(local_1bc / 2.0 + local_1c4);
          local_c = (int)(local_1d0 + -8.0);
        }
        if ((((*(float *)(local_194 + 0x2c) != (float)local_18) ||
             (*(float *)(local_194 + 0x30) != (float)local_14)) ||
            (*(float *)(local_194 + 0x34) != (float)local_10)) ||
           (*(float *)(local_194 + 0x38) != (float)local_c)) {
          FUN_006886a0(local_194 + 0x18,local_18,local_14,local_10,local_c);
        }
        local_1a4 = DAT_00920ef4;
        DAT_00920ef4 = DAT_00920ef4 + 0.03;
        DAT_02cecf74 = 1;
        pfVar5 = (float *)(**(code **)(*(int *)(*(int *)(local_194 + 8) + 0x18) + 0xc))();
        local_184 = *pfVar5;
        local_180 = pfVar5[1];
        local_17c = pfVar5[2];
        FUN_00616e80(local_194 + 0x18);
        cVar1 = FUN_004db510(*(undefined4 *)(local_194 + 8));
        if ((cVar1 == '\0') || (cVar1 = FUN_004db510(local_198), cVar1 == '\0')) {
          puVar6 = (undefined4 *)(**(code **)(*(int *)(local_198 + 0x18) + 0xc))();
          local_190 = *puVar6;
          local_18c = (float)puVar6[1];
          local_188 = puVar6[2];
          if (local_18c < local_180) {
            local_18c = local_180;
          }
          iVar3 = (**(code **)(*(int *)(local_198 + 0x18) + 0x30))();
          puVar6 = (undefined4 *)FUN_004795e0(local_1f4,iVar3 + 0x20);
          local_b8 = *puVar6;
          local_b4 = puVar6[1];
          local_b0 = puVar6[2];
          local_60 = local_b8;
          local_5c = local_b4;
          local_58 = local_b0;
          puVar6 = (undefined4 *)
                   FUN_004401a0(local_230,local_184,local_180,local_17c,local_190,local_18c,
                                local_188);
          local_ac = *puVar6;
          local_a8 = puVar6[1];
          local_a4 = puVar6[2];
          local_54 = local_ac;
          local_50 = local_a8;
          local_4c = local_a4;
          pfVar5 = (float *)FUN_004621a0(local_218,&local_ac);
          local_88 = *pfVar5;
          local_84 = pfVar5[1];
          local_80 = pfVar5[2];
          local_48 = local_88;
          local_44 = local_84;
          local_40 = local_80;
          puVar6 = (undefined4 *)FUN_004440d0(local_200,&local_b8,&local_88);
          local_a0 = *puVar6;
          local_9c = puVar6[1];
          local_98 = puVar6[2];
          local_30 = local_a0;
          local_2c = local_9c;
          local_28 = local_98;
          puVar6 = (undefined4 *)FUN_004621a0(local_20c,&local_a0);
          local_a0 = *puVar6;
          local_9c = puVar6[1];
          local_98 = puVar6[2];
          local_3c = local_a0;
          local_38 = local_9c;
          local_34 = local_98;
          puVar6 = (undefined4 *)FUN_004440d0(local_224,&local_88,&local_a0);
          local_94 = *puVar6;
          local_90 = puVar6[1];
          local_8c = puVar6[2];
          local_24 = local_94;
          local_20 = local_90;
          local_1c = local_8c;
          iVar3 = FUN_00462400();
          local_1ac = *(float *)(iVar3 + 0xc) * 2.0;
          local_78 = (double)(local_184 - local_1ac * local_88);
          local_70 = (double)(local_180 - local_1ac * local_84);
          local_68 = (double)(local_17c - local_1ac * local_80);
          FUN_00689090(local_194 + 0x18,&local_a0);
        }
        else if (*(int *)(local_194 + 0x10) == 0) {
          pfVar5 = (float *)FUN_0045c4d0();
          pfVar8 = local_f8;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *pfVar8 = *pfVar5;
            pfVar5 = pfVar5 + 1;
            pfVar8 = pfVar8 + 1;
          }
          local_19c = (float *)FUN_00462400();
          local_d0 = (double)(*local_19c * local_f8[0] + local_19c[1] * local_f8[3] +
                             local_19c[2] * local_e0) + local_d0;
          local_c8 = (double)(*local_19c * local_f8[1] + local_19c[1] * local_e8 +
                             local_19c[2] * local_dc) + local_c8;
          local_c0 = (double)(*local_19c * local_f8[2] + local_19c[1] * local_e4 +
                             local_19c[2] * local_d8) + local_c0;
          FUN_00689090(local_194 + 0x18,local_f8);
        }
        else {
          puVar6 = (undefined4 *)FUN_0062e070(local_270,*(undefined4 *)(local_194 + 0x10),0);
          puVar9 = local_178;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar9 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar9 = puVar9 + 1;
          }
          puVar6 = local_178;
          puVar9 = local_138;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar9 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar9 = puVar9 + 1;
          }
          FUN_00689090(local_194 + 0x18,local_138);
        }
        DAT_00920ef4 = *(float *)(local_194 + 0x28);
        local_19d = FUN_00685560();
        FUN_00685580(0);
        FUN_006869c0(local_18,local_14,local_10,local_c,
                     (uint)DAT_02cd9120 << 0x10 | 0xff000000 | (uint)DAT_02cd9121 << 8 |
                     (uint)DAT_02cd9122);
        FUN_00685580(local_19d);
        uVar2 = FUN_005d6130();
        FUN_00616500(local_194 + 0x18,uVar2);
        FUN_00584d30(local_194 + 0x18);
        FUN_004d4610(local_194 + 0x18);
        local_1a8 = FUN_004978b0();
        if (local_1a8 != 0) {
          local_1a8 = FUN_0081cb40("names",local_1a8);
          DAT_00920ef4 = local_1a4;
          uVar7 = FUN_00492ce0();
          std::_Init_atomic_counter(DAT_0091552c,uVar7);
          local_1e8 = FUN_00689eb0();
          local_1e0 = FUN_00689eb0();
          FUN_00689d10(DAT_0091552c,DAT_00917580,(int)(((float)local_1e0 * 5.0) / 2.0) + local_18,
                       (int)((local_1e8._4_4_ * 45.0) / 2.0) + local_14,local_1a8);
        }
        DAT_00920ef4 = local_1a4 + 0.01;
        FUN_0043fb00(&DAT_0100ff00,local_18 + -2,local_14 + -2,local_10 + 2,local_c + 2);
        DAT_00920ef4 = local_1a4;
        DAT_02cecf74 = 0;
        FUN_00684f10();
        local_1d4 = (int)((DAT_00920eb8 - 0.026) * (float)DAT_02cecee4);
        local_1d8 = (int)((DAT_00920ebc + 0.048) * (float)DAT_02cecee4);
        if (DAT_00915567 == '\0') {
          fVar10 = (DAT_00920ec8 - 0.035) * (float)DAT_02cecee0;
          fVar11 = (DAT_00920ec4 + 0.045) * (float)DAT_02cecee0;
        }
        else {
          fVar10 = (DAT_00920ec8 - 0.028) * (float)DAT_02cecee0;
          fVar11 = (DAT_00920ec4 + 0.04) * (float)DAT_02cecee0;
        }
        local_1b8 = (int)fVar11;
        local_1c0 = (int)fVar10;
        uVar4 = FUN_004d9b40(DAT_00918368,local_1c0,local_1d4,local_1b8,local_1d8,0,0);
        FUN_0068ca30(DAT_00917580,uVar4);
      }
    }
  }
  FUN_0083e885();
  return;
}

