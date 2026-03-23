
void __thiscall FUN_005e2d90(int *param_1,float param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  undefined4 *puVar8;
  float10 fVar9;
  undefined1 local_3d0 [64];
  undefined1 local_390 [120];
  undefined1 local_318 [12];
  undefined1 local_30c [12];
  undefined1 local_300 [12];
  undefined1 local_2f4 [12];
  undefined1 local_2e8 [12];
  undefined1 local_2dc [12];
  undefined1 local_2d0 [36];
  undefined1 local_2ac [24];
  undefined1 local_294 [12];
  float local_288;
  undefined4 local_284;
  float local_280;
  float local_27c;
  float local_278;
  float local_274;
  float local_270;
  float local_26c;
  float local_268;
  float local_264;
  float local_260;
  float local_25c;
  float local_258;
  float local_254;
  float local_250;
  float local_24c;
  float local_248;
  undefined4 *local_244;
  float local_240;
  float local_23c;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float *local_1e8;
  float local_1e4;
  float local_1e0;
  int *local_1dc;
  int *local_1d8;
  undefined4 *local_1d4;
  int *local_1d0;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  float local_190;
  float local_18c;
  float local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  float local_174;
  undefined4 local_170;
  undefined4 local_16c [16];
  undefined4 local_12c [10];
  double local_104;
  double local_fc;
  double local_f4;
  int local_ec;
  int local_e8;
  int local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  int local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  float local_7c;
  undefined4 local_78;
  int local_74;
  int local_70;
  int local_6c;
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
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((float)param_1[0x8c] <= param_2 && param_2 != (float)param_1[0x8c]) {
    *(uint *)(param_1[0x3d] + 0x14) = *(uint *)(param_1[0x3d] + 0x14) | 0x200;
    *(undefined4 *)(param_1[0x8a] + 0x110) = 0;
  }
  local_1d0 = param_1;
  local_1dc = (int *)FUN_00462610();
  if (local_1dc != (int *)0x0) {
    uVar2 = FUN_0045c4b0();
    if ((uVar2 & 1) != 0) {
      FUN_0049f450();
    }
    (**(code **)(local_1dc[6] + 0x30))();
    iVar3 = FUN_00477d70();
    if (iVar3 == 0) {
      (**(code **)(local_1dc[6] + 0x30))();
      iVar3 = FUN_00417e20();
      if ((iVar3 == 0) || (cVar1 = (**(code **)(*local_1dc + 0x6c))(), cVar1 != '\0'))
      goto LAB_005e2f93;
    }
    iVar3 = FUN_00462400();
    iVar4 = FUN_00462400();
    local_228 = *(float *)(iVar3 + 0xc) + *(float *)(iVar4 + 0xc);
    (**(code **)(local_1dc[6] + 0xc))();
    puVar5 = (undefined4 *)(**(code **)(local_1d0[6] + 0xc))();
    fVar9 = (float10)FUN_004620b0(*puVar5,puVar5[1],puVar5[2]);
    local_250 = (float)fVar9;
    if (local_250 < local_228 * local_228 * 0.5) {
      *(uint *)(local_1d0[0x3d] + 0x14) = *(uint *)(local_1d0[0x3d] + 0x14) | 0x200;
      *(undefined4 *)(local_1d0[0x8a] + 0x110) = 0;
    }
  }
LAB_005e2f93:
  local_1d0[0x8c] = (int)((float)local_1d0[0x8c] - param_2);
  local_244 = (undefined4 *)(local_1d0[0x3d] + 0x20);
  local_1e8 = (float *)(local_1d0[0x3d] + 0x38);
  local_1d0[0x51] = 0;
  local_1d0[0x52] = -0x3ee33333;
  local_1d0[0x53] = 0;
  local_1d4 = local_244;
  piVar6 = (int *)FUN_00440000();
  local_20 = *piVar6;
  local_1c = piVar6[1];
  local_18 = piVar6[2];
  local_1d0[0x54] = local_20;
  local_1d0[0x55] = local_1c;
  local_1d0[0x56] = local_18;
  fVar9 = (float10)FUN_004e9610();
  local_1e4 = (float)fVar9;
  local_280 = local_1e4 * *(float *)(local_1d0[0x3e] + 0x174);
  local_21c = local_1e4 * *(float *)(local_1d0[0x3e] + 0x178);
  local_1f4 = local_1e4 * *(float *)(local_1d0[0x3e] + 0x17c);
  local_27c = local_1e4 * *(float *)(local_1d0[0x3e] + 0x180);
  local_20c = local_1e4 * *(float *)(local_1d0[0x3e] + 0x184);
  local_26c = local_1e4 * *(float *)(local_1d0[0x3e] + 0x188);
  puVar5 = (undefined4 *)FUN_00447f60();
  local_68 = *puVar5;
  local_64 = puVar5[1];
  local_60 = puVar5[2];
  local_5c = puVar5[3];
  local_58 = puVar5[4];
  local_54 = puVar5[5];
  FUN_00444f70(local_1d0[0x3c],local_68,local_64,local_60,local_5c,local_58,local_54);
  local_1e0 = (float)(*(double *)(local_1d4 + 0xc) - (double)local_1e0);
  puVar5 = (undefined4 *)FUN_0049c4f0();
  local_1c0 = *puVar5;
  local_1bc = puVar5[1];
  local_1b8 = puVar5[2];
  local_1b4 = puVar5[3];
  local_1b0 = puVar5[4];
  local_1ac = puVar5[5];
  puVar5 = (undefined4 *)FUN_00447f60();
  local_1a8 = *puVar5;
  local_1a4 = puVar5[1];
  local_1a0 = puVar5[2];
  local_19c = puVar5[3];
  local_198 = puVar5[4];
  local_194 = puVar5[5];
  puVar5 = (undefined4 *)
           FUN_004e9580(local_390,local_1a8,local_1a4,local_1a0,local_19c,local_198,local_194,
                        0x3fe0000000000000,local_1c0,local_1bc,local_1b8);
  local_e0 = *puVar5;
  local_dc = puVar5[1];
  local_d8 = puVar5[2];
  local_d4 = puVar5[3];
  local_d0 = puVar5[4];
  local_cc = puVar5[5];
  FUN_00444f70(local_1d0[0x3c],local_e0,local_dc,local_d8,local_d4,local_d0,local_cc);
  local_1fc = (float)(*(double *)(local_1d4 + 0xc) - (double)local_1fc);
  puVar5 = (undefined4 *)FUN_00440130();
  local_178 = *puVar5;
  local_174 = (float)puVar5[1];
  local_170 = puVar5[2];
  local_2c = local_178;
  local_28 = local_174;
  local_24 = local_170;
  puVar5 = (undefined4 *)FUN_004621a0();
  local_178 = *puVar5;
  local_174 = (float)puVar5[1];
  local_170 = puVar5[2];
  local_80 = local_178;
  local_7c = local_174;
  local_78 = local_170;
  fVar9 = (float10)FUN_0047b6f0();
  local_1e0 = (float)fVar9;
  local_238 = *(float *)(local_1d0[0x3e] + 0x170);
  if (local_1e0 <= 0.0) {
    local_214 = 0.0;
  }
  else {
    if (local_238 <= 0.0) {
      local_224 = 2.0;
    }
    else {
      local_224 = (local_1e0 * local_174) / local_238;
    }
    local_214 = local_224;
  }
  local_1f8 = local_214;
  if (local_214 <= 1.0) {
    local_1f0 = 1.0;
  }
  else {
    local_234 = local_214 - 1.0;
    local_1f0 = 0.9 / (local_234 * 0.25 * local_234 + 1.0) + 0.1;
  }
  local_1ec = 9.8 - local_174 * 19.6 * (local_214 - 1.0);
  local_268 = -4.9;
  fVar9 = (float10)FUN_004428b0();
  local_270 = (float)fVar9;
  local_278 = local_268 * local_270 * local_1f0;
  local_1ec = local_1ec + local_278;
  if (0.0 < local_1ec) {
    piVar6 = (int *)FUN_00439d00(local_2ac,local_1d0[0x51],local_1d0[0x52],local_1d0[0x53],local_1ec
                                );
    local_b0 = *piVar6;
    local_ac = piVar6[1];
    local_a8 = piVar6[2];
    local_1d0[0x51] = local_b0;
    local_1d0[0x52] = local_ac;
    local_1d0[0x53] = local_a8;
  }
  local_1d0[0x54] = (int)(-local_21c * (float)local_1d0[0x4e]);
  local_1d0[0x56] = (int)(-local_21c * (float)local_1d0[0x50]);
  local_14 = local_178;
  local_10 = local_174 + 2.0;
  local_c = local_170;
  puVar5 = (undefined4 *)FUN_004621a0();
  local_98 = *puVar5;
  local_94 = puVar5[1];
  local_90 = puVar5[2];
  local_22c = local_280 * local_1f0;
  local_14 = local_98;
  local_10 = (float)local_94;
  local_c = local_90;
  fVar9 = (float10)FUN_004428b0();
  local_288 = (float)fVar9;
  local_1d0[0x54] = (int)((float)local_1d0[0x54] - local_288 * local_22c);
  fVar9 = (float10)FUN_004428b0();
  local_260 = (float)fVar9;
  local_1d0[0x56] = (int)(local_260 * local_22c + (float)local_1d0[0x56]);
  local_284 = *(undefined4 *)(local_1d0[0x8a] + 0xc4);
  if (0.0 < local_20c) {
    fVar9 = (float10)FUN_00447ed0();
    local_24c = (float)fVar9;
    local_1d0[0x55] = (int)(local_24c * local_26c);
  }
  local_190 = *local_1e8 * local_1f4 - (float)local_1d0[0x4b];
  local_18c = local_1e8[1] * local_1f4 - (float)local_1d0[0x4c];
  local_188 = local_1e8[2] * local_1f4 - (float)local_1d0[0x4d];
  if (param_2 == 0.0) {
    local_210 = 1e+30;
  }
  else {
    local_210 = 1.0 / param_2;
  }
  local_254 = local_210;
  puVar5 = (undefined4 *)FUN_004462d0(local_294,local_210);
  local_184 = *puVar5;
  local_180 = puVar5[1];
  local_17c = puVar5[2];
  local_38 = local_184;
  local_34 = local_180;
  local_30 = local_17c;
  fVar9 = (float10)FUN_004428b0();
  local_218 = (float)fVar9;
  if (local_218 < 0.0) {
    puVar5 = (undefined4 *)FUN_00439d00(local_30c,local_184,local_180,local_17c,-local_218);
    local_184 = *puVar5;
    local_180 = puVar5[1];
    local_17c = puVar5[2];
    local_44 = local_184;
    local_40 = local_180;
    local_3c = local_17c;
  }
  local_204 = local_27c * local_1f0;
  fVar9 = (float10)FUN_004428b0();
  local_220 = (float)fVar9;
  if (local_204 * local_204 < local_220) {
    fVar9 = (float10)FUN_00820570((double)local_220);
    local_274 = (float)fVar9;
    local_25c = local_274;
    puVar5 = (undefined4 *)FUN_004462d0(local_2dc,local_274 * local_204);
    local_184 = *puVar5;
    local_180 = puVar5[1];
    local_17c = puVar5[2];
    local_50 = local_184;
    local_4c = local_180;
    local_48 = local_17c;
  }
  piVar6 = (int *)FUN_00440130();
  local_74 = *piVar6;
  local_70 = piVar6[1];
  local_6c = piVar6[2];
  local_1d0[0x51] = local_74;
  local_1d0[0x52] = local_70;
  local_1d0[0x53] = local_6c;
  piVar6 = (int *)FUN_00439d00(local_2e8,local_1d0[0x4b],local_1d0[0x4c],local_1d0[0x4d],
                               param_2 * 0.5);
  local_8c = *piVar6;
  local_88 = piVar6[1];
  local_84 = piVar6[2];
  local_1d0[0x4b] = local_8c;
  local_1d0[0x4c] = local_88;
  local_1d0[0x4d] = local_84;
  piVar6 = (int *)FUN_00439d00(local_2d0,local_1d0[0x4e],local_1d0[0x4f],local_1d0[0x50],
                               param_2 * 0.5);
  local_a4 = *piVar6;
  local_a0 = piVar6[1];
  local_9c = piVar6[2];
  local_1d0[0x4e] = local_a4;
  local_1d0[0x4f] = local_a0;
  local_1d0[0x50] = local_9c;
  fVar9 = (float10)FUN_0045c420();
  local_1d0[0x47] = (int)(float)fVar9;
  if ((float)local_1d0[0x47] <= 0.0) {
    local_208 = 1e+30;
  }
  else {
    local_208 = 1.0 / (float)local_1d0[0x47];
  }
  local_1d0[0x48] = (int)local_208;
  local_1d8 = (int *)(local_1d0[0x8a] + 0x4c);
  FUN_005a9a50();
  if ((*local_1d8 != 0) && (local_1d8[1] == 0)) {
    (**(code **)(*local_1d0 + 0x48))();
  }
  if (*local_1d8 == 0) {
    *(double *)(local_1d4 + 10) =
         (double)((float)local_1d0[0x4b] * param_2) + *(double *)(local_1d4 + 10);
    *(double *)(local_1d4 + 0xc) =
         (double)((float)local_1d0[0x4c] * param_2) + *(double *)(local_1d4 + 0xc);
    *(double *)(local_1d4 + 0xe) =
         (double)((float)local_1d0[0x4d] * param_2) + *(double *)(local_1d4 + 0xe);
  }
  else {
    if ((float)local_1d8[0x14] <= 0.0 && (float)local_1d8[0x14] != 0.0) {
      local_1d8[0x14] = 0;
    }
    *(double *)(local_1d4 + 10) =
         (double)((float)local_1d0[0x4b] * (float)local_1d8[0x14]) + *(double *)(local_1d4 + 10);
    *(double *)(local_1d4 + 0xc) =
         (double)((float)local_1d0[0x4c] * (float)local_1d8[0x14]) + *(double *)(local_1d4 + 0xc);
    *(double *)(local_1d4 + 0xe) =
         (double)((float)local_1d0[0x4d] * (float)local_1d8[0x14]) + *(double *)(local_1d4 + 0xe);
    fVar9 = (float10)FUN_004428b0(local_1d0 + 0x4b,local_1d8 + 0x1b);
    local_264 = (float)fVar9;
    piVar6 = (int *)FUN_00439d00(local_300,local_1d0[0x4b],local_1d0[0x4c],local_1d0[0x4d],
                                 local_264 * -1.5);
    local_c8 = *piVar6;
    local_c4 = piVar6[1];
    local_c0 = piVar6[2];
    local_1d0[0x4b] = local_c8;
    local_1d0[0x4c] = local_c4;
    local_1d0[0x4d] = local_c0;
    *(double *)(local_1d4 + 10) =
         (double)((param_2 - (float)local_1d8[0x14]) * (float)local_1d0[0x4b]) +
         *(double *)(local_1d4 + 10);
    *(double *)(local_1d4 + 0xc) =
         (double)((param_2 - (float)local_1d8[0x14]) * (float)local_1d0[0x4c]) +
         *(double *)(local_1d4 + 0xc);
    *(double *)(local_1d4 + 0xe) =
         (double)((param_2 - (float)local_1d8[0x14]) * (float)local_1d0[0x4d]) +
         *(double *)(local_1d4 + 0xe);
    FUN_00442900();
  }
  puVar5 = (undefined4 *)FUN_00444d50(local_3d0,local_1d4,local_1d0[0x4e]);
  puVar8 = local_16c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar5 = local_16c;
  puVar8 = local_1d4;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  piVar6 = (int *)FUN_00439d00(local_318,local_1d0[0x4b],local_1d0[0x4c],local_1d0[0x4d],
                               param_2 * 0.5);
  local_ec = *piVar6;
  local_e8 = piVar6[1];
  local_e4 = piVar6[2];
  local_1d0[0x4b] = local_ec;
  local_1d0[0x4c] = local_e8;
  local_1d0[0x4d] = local_e4;
  piVar6 = (int *)FUN_00439d00(local_2f4,local_1d0[0x4e],local_1d0[0x4f],local_1d0[0x50],
                               param_2 * 0.5);
  local_bc = *piVar6;
  local_b8 = piVar6[1];
  local_b4 = piVar6[2];
  local_1d0[0x4e] = local_bc;
  local_1d0[0x4f] = local_b8;
  local_1d0[0x50] = local_b4;
  fVar9 = (float10)FUN_0045c420();
  local_1d0[0x47] = (int)(float)fVar9;
  if ((float)local_1d0[0x47] <= 0.0) {
    local_230 = 1e+30;
  }
  else {
    local_230 = 1.0 / (float)local_1d0[0x47];
  }
  local_1d0[0x48] = (int)local_230;
  piVar6 = (int *)local_1d0[0x8a];
  piVar7 = local_1d0 + 0x45;
  for (iVar3 = 0x12; piVar6 = piVar6 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = *piVar7;
    piVar7 = piVar7 + 1;
  }
  FUN_004db100();
  if ((*(uint *)(local_1d0[0x3d] + 0x14) & 0x1000200) != 0) {
    if (*(float *)(local_1d0[0x8a] + 0x110) <= 0.0) {
      cVar1 = FUN_004b9830();
      if (cVar1 == '\0') {
        (**(code **)(local_1d0[6] + 0x14))();
      }
    }
    else {
      *(float *)(local_1d0[0x8a] + 0x110) = *(float *)(local_1d0[0x8a] + 0x110) - param_2;
      fVar9 = (float10)FUN_004a7890();
      local_240 = (float)fVar9;
      if (local_240 * 0.5 + 0.5 < param_2 * 5.0) {
        local_200 = *(float *)(local_1d0[0x3c] + 0x14) * 0.7;
        puVar5 = (undefined4 *)(local_1d0[0x3d] + 0x20);
        puVar8 = local_12c;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar8 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar8 = puVar8 + 1;
        }
        fVar9 = (float10)FUN_004464c0();
        local_248 = (float)fVar9;
        local_104 = (double)(local_248 * local_200 + (float)local_1d0[0x42]);
        fVar9 = (float10)FUN_004464c0();
        local_23c = (float)fVar9;
        local_fc = (double)(local_23c * local_200 + (float)local_1d0[0x43]);
        fVar9 = (float10)FUN_004464c0();
        local_258 = (float)fVar9;
        local_f4 = (double)(local_258 * local_200 + (float)local_1d0[0x44]);
        FUN_004cb7b0();
      }
    }
  }
  FUN_0083e885();
  return;
}

