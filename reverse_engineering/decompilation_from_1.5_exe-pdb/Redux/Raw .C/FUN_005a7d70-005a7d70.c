
void FUN_005a7d70(float param_1)

{
  char cVar1;
  float *pfVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_404 [60];
  undefined1 local_3c8 [36];
  undefined1 local_3a4 [24];
  undefined1 local_38c [12];
  undefined1 local_380 [24];
  undefined1 local_368 [24];
  undefined1 local_350 [36];
  undefined1 local_32c [24];
  undefined1 local_314 [24];
  undefined1 local_2fc [24];
  undefined4 local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  int local_2a4;
  float local_2a0;
  int local_29c;
  int local_298;
  float local_294;
  float local_290;
  float local_28c;
  float local_288;
  float local_284;
  float local_280;
  float local_27c;
  float local_278;
  float local_274;
  float local_270;
  float local_26c;
  int *local_268;
  undefined4 *local_264;
  int *local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  float local_24c;
  undefined4 local_248;
  undefined4 local_244;
  float local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  float local_21c;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  float local_208;
  float local_204;
  float local_200;
  undefined4 local_1fc [16];
  undefined4 local_1bc [19];
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  int local_14c;
  int local_148;
  int local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  int local_134;
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  int local_120;
  float local_11c;
  float local_118;
  float local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined4 local_98;
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
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
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_004b9830();
  if (cVar1 == '\0') {
    if ((*(uint *)(local_260[0x3d] + 0x14) & 0x1000000) != 0) {
      (**(code **)(local_260[6] + 0x14))();
      goto LAB_005a98e5;
    }
    if ((*(uint *)(local_260[0x3d] + 0x14) & 0x200) != 0) {
      (**(code **)(local_260[6] + 0x10))();
      goto LAB_005a98e5;
    }
  }
  local_260[0x51] = 0;
  local_260[0x52] = -0x3ee33333;
  local_260[0x53] = 0;
  pfVar2 = (float *)FUN_00440000();
  local_208 = *pfVar2;
  local_204 = pfVar2[1];
  local_200 = pfVar2[2];
  local_264 = (undefined4 *)(local_260[0x3d] + 0x20);
  local_f8 = local_208;
  local_f4 = local_204;
  local_f0 = local_200;
  puVar3 = (undefined4 *)FUN_00439d80();
  local_250 = *puVar3;
  local_24c = (float)puVar3[1];
  local_248 = puVar3[2];
  local_80 = local_250;
  local_7c = local_24c;
  local_78 = local_248;
  puVar3 = (undefined4 *)FUN_004795e0();
  local_170 = *puVar3;
  local_16c = puVar3[1];
  local_168 = puVar3[2];
  local_140 = local_170;
  local_13c = local_16c;
  local_138 = local_168;
  puVar3 = (undefined4 *)FUN_004560b0();
  local_244 = *puVar3;
  local_240 = (float)puVar3[1];
  local_23c = puVar3[2];
  local_98 = local_244;
  local_94 = local_240;
  local_90 = local_23c;
  if ((*(uint *)(local_260[0x8a] + 0x114) & 4) == 0) {
    puVar3 = (undefined4 *)FUN_00447f60();
    local_68 = *puVar3;
    local_64 = puVar3[1];
    local_60 = puVar3[2];
    local_5c = puVar3[3];
    local_58 = puVar3[4];
    local_54 = puVar3[5];
    FUN_00444f70(local_260[0x3c],local_68,local_64);
    if (local_29c == 0) {
      local_2a4 = 0;
    }
    else {
      local_2a4 = FUN_00479f30();
    }
    local_298 = local_2a4;
    if ((local_2a4 != 0) && (cVar1 = (**(code **)(*local_260 + 0x60))(), cVar1 != '\0')) {
      *(uint *)(local_260[0x8a] + 0x114) = *(uint *)(local_260[0x8a] + 0x114) | 4;
    }
    local_2c4 = *(float *)(local_260[0x8a] + 0xc4);
    puVar3 = (undefined4 *)FUN_00440000();
    local_38 = *puVar3;
    local_34 = puVar3[1];
    local_30 = puVar3[2];
    local_20 = local_38;
    local_1c = local_34;
    local_18 = local_30;
    puVar3 = (undefined4 *)FUN_004621a0();
    local_44 = *puVar3;
    local_40 = puVar3[1];
    local_3c = puVar3[2];
    local_208 = local_208 - (float)local_260[0x4e] * 10.0;
    local_204 = local_204 - (float)local_260[0x4f] * 10.0;
    local_200 = local_200 - (float)local_260[0x50] * 10.0;
    local_20 = local_44;
    local_1c = local_40;
    local_18 = local_3c;
    fVar7 = (float10)FUN_004428b0();
    local_2bc = (float)fVar7;
    local_208 = local_208 - local_2bc * 25.0;
    local_204 = local_2c4 * 20.0 + local_204;
    fVar7 = (float10)FUN_004428b0();
    local_2cc = (float)fVar7;
    local_200 = local_2cc * 25.0 + local_200;
    local_288 = 9.8 - (float)((*(double *)(local_264 + 0xc) - 1.0) - (double)local_2d4) * 19.6 *
                      local_21c;
    if (0.0 < local_288) {
      piVar4 = (int *)FUN_00439d00(local_350);
      local_128 = *piVar4;
      local_124 = piVar4[1];
      local_120 = piVar4[2];
      local_260[0x51] = local_128;
      local_260[0x52] = local_124;
      local_260[0x53] = local_120;
    }
    fVar7 = (float10)FUN_004428b0();
    local_2dc = (float)fVar7;
    piVar4 = (int *)FUN_00439d00(local_3c8);
    local_e0 = *piVar4;
    local_dc = piVar4[1];
    local_d8 = piVar4[2];
    local_260[0x51] = local_e0;
    local_260[0x52] = local_dc;
    local_260[0x53] = local_d8;
    local_2a8 = 1.0 / (param_1 + 1.1754944e-38);
    puVar3 = (undefined4 *)FUN_00439d00(local_368);
    local_25c = *puVar3;
    local_258 = puVar3[1];
    local_254 = puVar3[2];
    local_158 = local_25c;
    local_154 = local_258;
    local_150 = local_254;
    puVar3 = (undefined4 *)FUN_004462d0();
    local_214 = *puVar3;
    local_210 = puVar3[1];
    local_20c = puVar3[2];
    local_50 = local_214;
    local_4c = local_210;
    local_48 = local_20c;
    fVar7 = (float10)FUN_004428b0();
    local_2b0 = (float)fVar7;
    puVar3 = (undefined4 *)FUN_00439d00(local_380);
    local_214 = *puVar3;
    local_210 = puVar3[1];
    local_20c = puVar3[2];
    local_278 = (float)local_260[0x47] * 4.0 + 6.0;
    local_74 = local_214;
    local_70 = local_210;
    local_6c = local_20c;
    fVar7 = (float10)FUN_004428b0();
    local_294 = (float)fVar7;
    if (local_278 * local_278 < local_294) {
      fVar7 = (float10)FUN_00820570();
      local_2d8 = (float)fVar7;
      local_2b8 = local_2d8;
      puVar3 = (undefined4 *)FUN_004462d0();
      local_214 = *puVar3;
      local_210 = puVar3[1];
      local_20c = puVar3[2];
      local_8c = local_214;
      local_88 = local_210;
      local_84 = local_20c;
    }
    piVar4 = (int *)FUN_00440130();
    local_a4 = *piVar4;
    local_a0 = piVar4[1];
    local_9c = piVar4[2];
    local_260[0x51] = local_a4;
    local_260[0x52] = local_a0;
    local_260[0x53] = local_9c;
  }
  else if ((*(uint *)(local_260[0x8a] + 0x114) & 1) == 0) {
    if (((*(uint *)(local_260[0x8a] + 0x114) & 8) != 0) &&
       ((float)local_260[0x4c] <= -0.0 && (float)local_260[0x4c] != -0.0)) {
      *(uint *)(local_260[0x8a] + 0x114) = *(uint *)(local_260[0x8a] + 0x114) & 0xfffffff7;
      *(uint *)(local_260[0x8a] + 0x114) = *(uint *)(local_260[0x8a] + 0x114) | 1;
    }
  }
  else {
    local_2e4 = *(undefined4 *)(local_260[0x8a] + 0xc4);
    if (*(int *)(local_260[0x8a] + 0xd4) == 0) {
      local_280 = *(float *)(local_260[0x8a] + 0xd0);
    }
    else {
      local_280 = 2.0;
    }
    local_26c = local_280;
    local_270 = *(float *)(local_260[0x8a] + 0xcc);
    local_27c = local_280 * local_280 + local_270 * local_270;
    if (1.0 < local_27c) {
      local_27c = 1.0;
    }
    local_208 = ((local_208 - (float)local_260[0x4e] * 1.0) - local_240 * 5.0) - local_280 * 1.0;
    local_200 = local_270 * 1.0 + local_24c * 5.0 + (local_200 - (float)local_260[0x50] * 1.0);
    local_2b4 = local_27c * 0.5 + 2.0;
    fVar7 = (float10)FUN_00447ed0();
    local_2e0 = (float)fVar7;
    local_204 = local_2e0 * 2.0 + local_204;
    if (local_26c <= 0.0) {
      local_284 = 10.0;
    }
    else {
      local_284 = 15.0;
    }
    puVar3 = (undefined4 *)FUN_00459570(local_404,local_26c * local_284);
    local_238 = *puVar3;
    local_234 = puVar3[1];
    local_230 = puVar3[2];
    local_110 = local_238;
    local_10c = local_234;
    local_108 = local_230;
    puVar3 = (undefined4 *)FUN_004401a0();
    local_238 = *puVar3;
    local_ac = puVar3[1];
    local_230 = puVar3[2];
    local_234 = 0;
    local_b0 = local_238;
    local_a8 = local_230;
    puVar3 = (undefined4 *)FUN_004462d0();
    local_22c = *puVar3;
    local_228 = puVar3[1];
    local_224 = puVar3[2];
    local_274 = 5.0;
    local_164 = local_22c;
    local_160 = local_228;
    local_15c = local_224;
    fVar7 = (float10)FUN_004428b0();
    local_28c = (float)fVar7;
    if (local_274 * local_274 < local_28c) {
      fVar7 = (float10)FUN_00820570();
      local_2c8 = (float)fVar7;
      local_2ac = local_2c8;
      puVar3 = (undefined4 *)FUN_004462d0();
      local_22c = *puVar3;
      local_228 = puVar3[1];
      local_224 = puVar3[2];
      local_2c = local_22c;
      local_28 = local_228;
      local_24 = local_224;
    }
    piVar4 = (int *)FUN_00440130();
    local_c8 = *piVar4;
    local_c4 = piVar4[1];
    local_c0 = piVar4[2];
    local_260[0x51] = local_c8;
    local_260[0x52] = local_c4;
    local_260[0x53] = local_c0;
    if ((float)local_260[0x4c] <= 0.0 && (float)local_260[0x4c] != 0.0) {
      local_260[0x52] =
           (int)((float)local_260[0x4c] * 0.1 * (float)local_260[0x4c] + (float)local_260[0x52]);
    }
  }
  piVar4 = (int *)FUN_00439d00(local_2fc);
  local_bc = *piVar4;
  local_b8 = piVar4[1];
  local_b4 = piVar4[2];
  local_260[0x4b] = local_bc;
  local_260[0x4c] = local_b8;
  local_260[0x4d] = local_b4;
  piVar4 = (int *)FUN_00439d00(local_314);
  local_d4 = *piVar4;
  local_d0 = piVar4[1];
  local_cc = piVar4[2];
  local_260[0x4e] = local_d4;
  local_260[0x4f] = local_d0;
  local_260[0x50] = local_cc;
  fVar7 = (float10)FUN_0045c420();
  local_260[0x47] = (int)(float)fVar7;
  if ((float)local_260[0x47] <= 0.0) {
    local_2a0 = 1e+30;
  }
  else {
    local_2a0 = 1.0 / (float)local_260[0x47];
  }
  local_260[0x48] = (int)local_2a0;
  local_268 = (int *)(local_260[0x8a] + 0x4c);
  if ((*(uint *)(local_260[0x8a] + 0x114) & 4) != 0) {
    FUN_005a9a50();
  }
  if (*local_268 == 0) {
    *(double *)(local_264 + 10) =
         (double)((float)local_260[0x4b] * param_1) + *(double *)(local_264 + 10);
    *(double *)(local_264 + 0xc) =
         (double)((float)local_260[0x4c] * param_1) + *(double *)(local_264 + 0xc);
    *(double *)(local_264 + 0xe) =
         (double)((float)local_260[0x4d] * param_1) + *(double *)(local_264 + 0xe);
  }
  else {
    if ((float)local_268[0x14] <= 0.0 && (float)local_268[0x14] != 0.0) {
      local_268[0x14] = 0;
    }
    *(double *)(local_264 + 10) =
         (double)((float)local_260[0x4b] * (float)local_268[0x14]) + *(double *)(local_264 + 10);
    *(double *)(local_264 + 0xc) =
         (double)((float)local_260[0x4c] * (float)local_268[0x14]) + *(double *)(local_264 + 0xc);
    *(double *)(local_264 + 0xe) =
         (double)((float)local_260[0x4d] * (float)local_268[0x14]) + *(double *)(local_264 + 0xe);
    fVar7 = (float10)FUN_004428b0();
    local_2d0 = (float)fVar7;
    piVar4 = (int *)FUN_00439d00(local_32c);
    local_ec = *piVar4;
    local_e8 = piVar4[1];
    local_e4 = piVar4[2];
    local_260[0x4b] = local_ec;
    local_260[0x4c] = local_e8;
    local_260[0x4d] = local_e4;
    *(double *)(local_264 + 10) =
         (double)((param_1 - (float)local_268[0x14]) * (float)local_260[0x4b]) +
         *(double *)(local_264 + 10);
    *(double *)(local_264 + 0xc) =
         (double)((param_1 - (float)local_268[0x14]) * (float)local_260[0x4c]) +
         *(double *)(local_264 + 0xc);
    *(double *)(local_264 + 0xe) =
         (double)((param_1 - (float)local_268[0x14]) * (float)local_260[0x4d]) +
         *(double *)(local_264 + 0xe);
  }
  if ((*(uint *)(local_260[0x8a] + 0x114) & 4) == 0) {
    puVar3 = (undefined4 *)FUN_00444d50();
    puVar6 = local_1bc;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar3 = local_1bc;
    puVar6 = local_264;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  else {
    pfVar2 = (float *)FUN_00440210();
    local_104 = *pfVar2;
    local_100 = pfVar2[1];
    local_fc = pfVar2[2];
    *(double *)(local_264 + 10) = (double)local_104 + *(double *)(local_264 + 10);
    *(double *)(local_264 + 0xc) = (double)local_100 + *(double *)(local_264 + 0xc);
    *(double *)(local_264 + 0xe) = (double)local_fc + *(double *)(local_264 + 0xe);
    local_14 = local_104;
    local_10 = local_100;
    local_c = local_fc;
    puVar3 = (undefined4 *)FUN_00444d50();
    puVar6 = local_1fc;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar3 = local_1fc;
    puVar6 = local_264;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    pfVar2 = (float *)FUN_00440210();
    local_11c = *pfVar2;
    local_118 = pfVar2[1];
    local_114 = pfVar2[2];
    *(double *)(local_264 + 10) = *(double *)(local_264 + 10) - (double)local_11c;
    *(double *)(local_264 + 0xc) = *(double *)(local_264 + 0xc) - (double)local_118;
    *(double *)(local_264 + 0xe) = *(double *)(local_264 + 0xe) - (double)local_114;
    local_14 = local_11c;
    local_10 = local_118;
    local_c = local_114;
  }
  if ((*(uint *)(local_260[0x8a] + 0x114) & 4) != 0) {
    if ((*local_268 == 0) &&
       (FUN_00785730(),
       *(double *)(local_264 + 0xc) <= (double)local_2c0 &&
       (double)local_2c0 != *(double *)(local_264 + 0xc))) {
      *local_268 = 1;
    }
    if (*local_268 != 0) {
      if ((*(uint *)(local_260[0x8a] + 0x114) & 1) != 0) {
        *(uint *)(local_260[0x8a] + 0x114) = *(uint *)(local_260[0x8a] + 0x114) & 0xfffffff6;
      }
      *(uint *)(local_260[0x8a] + 0x114) = *(uint *)(local_260[0x8a] + 0x114) & 0xfffffffb;
      iVar5 = FUN_00572a70();
      if (((iVar5 != 0) && (cVar1 = FUN_004b9860(), cVar1 != '\0')) &&
         (iVar5 = (**(code **)local_260[6])(), *(int *)(iVar5 + 0x14) != 0x5752434b)) {
        FUN_004b8000();
      }
    }
  }
  if (*local_268 != 0) {
    FUN_00442900();
  }
  piVar4 = (int *)FUN_00439d00(local_38c);
  local_134 = *piVar4;
  local_130 = piVar4[1];
  local_12c = piVar4[2];
  local_260[0x4e] = local_134;
  local_260[0x4f] = local_130;
  local_260[0x50] = local_12c;
  piVar4 = (int *)FUN_00439d00(local_3a4);
  local_14c = *piVar4;
  local_148 = piVar4[1];
  local_144 = piVar4[2];
  local_260[0x4b] = local_14c;
  local_260[0x4c] = local_148;
  local_260[0x4d] = local_144;
  fVar7 = (float10)FUN_0045c420();
  local_260[0x47] = (int)(float)fVar7;
  if ((float)local_260[0x47] <= 0.0) {
    local_290 = 1e+30;
  }
  else {
    local_290 = 1.0 / (float)local_260[0x47];
  }
  local_260[0x48] = (int)local_290;
  FUN_004db100();
LAB_005a98e5:
  FUN_0083e885();
  return;
}

