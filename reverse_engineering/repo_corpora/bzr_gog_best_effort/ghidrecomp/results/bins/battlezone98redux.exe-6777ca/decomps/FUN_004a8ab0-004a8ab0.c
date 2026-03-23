
void __thiscall FUN_004a8ab0(int *param_1,float param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  float *pfVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined1 local_478 [64];
  undefined1 local_438 [64];
  undefined1 local_3f8 [64];
  undefined1 local_3b8 [24];
  undefined1 local_3a0 [12];
  undefined1 local_394 [24];
  undefined1 local_37c [12];
  undefined1 local_370 [12];
  undefined1 local_364 [12];
  undefined1 local_358 [12];
  undefined1 local_34c [12];
  undefined1 local_340 [12];
  undefined1 local_334 [24];
  undefined1 local_31c [12];
  undefined1 local_310 [12];
  undefined1 local_304 [12];
  undefined1 local_2f8 [12];
  undefined1 local_2ec [12];
  undefined1 local_2e0 [12];
  undefined1 local_2d4 [12];
  undefined1 local_2c8 [12];
  undefined1 local_2bc [12];
  undefined1 local_2b0 [24];
  double local_298;
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
  float local_268;
  float local_264;
  float local_260;
  float local_25c;
  int local_258;
  float local_254;
  float local_250;
  float local_24c;
  uint local_248;
  float local_244;
  float local_240;
  float local_23c;
  int *local_238;
  int *local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  int local_200;
  int local_1fc;
  int local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  int local_1e8;
  float local_1e4;
  int local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  undefined4 local_1d0 [16];
  undefined4 local_190 [16];
  undefined4 local_150 [16];
  int local_110;
  int local_10c;
  int local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  int local_98;
  int local_94;
  int local_90;
  float local_8c;
  float local_88;
  float local_84;
  int local_80;
  float local_7c;
  int local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_238 = (int *)(param_1[0x8c] + 0x4c);
  local_234 = param_1;
  fVar8 = (float10)FUN_0045c420();
  local_234[0x47] = (int)(float)fVar8;
  if ((float)local_234[0x47] <= 0.0) {
    local_250 = 1e+30;
  }
  else {
    local_250 = 1.0 / (float)local_234[0x47];
  }
  local_234[0x48] = (int)local_250;
  uVar2 = FUN_00822d90();
  if (uVar2 < local_234[0x5a] + 1000U) {
    FUN_00442900();
  }
  if ((*local_238 == 0) && (cVar1 = (**(code **)(*local_234 + 0xa0))(), cVar1 == '\0')) {
    *(double *)(local_234[0x3d] + 0x48) =
         (double)(param_2 * (float)local_234[0x4b]) + *(double *)(local_234[0x3d] + 0x48);
    *(double *)(local_234[0x3d] + 0x50) =
         (double)(param_2 * (float)local_234[0x4c]) + *(double *)(local_234[0x3d] + 0x50);
    *(double *)(local_234[0x3d] + 0x58) =
         (double)(param_2 * (float)local_234[0x4d]) + *(double *)(local_234[0x3d] + 0x58);
    puVar3 = (undefined4 *)FUN_00444d50(local_3f8,local_234[0x3d] + 0x20,local_234[0x4e]);
    puVar7 = local_1d0;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar3 = local_1d0;
    puVar7 = (undefined4 *)(local_234[0x3d] + 0x20);
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  else {
    local_1e8 = local_234[0x4b];
    local_1e4 = (float)local_234[0x4c];
    local_1e0 = local_234[0x4d];
    local_1f4 = (float)local_238[0x1b];
    local_1f0 = (float)local_238[0x1c];
    local_1ec = (float)local_238[0x1d];
    pfVar4 = (float *)FUN_00440000(local_2c8);
    local_1dc = *pfVar4;
    local_1d8 = pfVar4[1];
    local_1d4 = pfVar4[2];
    local_68 = local_1dc;
    local_64 = local_1d8;
    local_60 = local_1d4;
    puVar3 = (undefined4 *)FUN_004401a0(local_364,local_238[0x15],local_238[0x16],local_238[0x17]);
    local_ec = *puVar3;
    local_e8 = puVar3[1];
    local_e4 = puVar3[2];
    local_23c = (float)local_238[0x14];
    local_14 = local_ec;
    local_10 = local_e8;
    local_c = local_e4;
    if (0.0 <= local_23c) {
      if (param_2 < local_23c) {
        local_23c = param_2;
      }
      *(double *)(local_234[0x3d] + 0x48) =
           (double)(local_23c * (float)local_234[0x4b]) + *(double *)(local_234[0x3d] + 0x48);
      *(double *)(local_234[0x3d] + 0x50) =
           (double)(local_23c * (float)local_234[0x4c]) + *(double *)(local_234[0x3d] + 0x50);
      *(double *)(local_234[0x3d] + 0x58) =
           (double)(local_23c * (float)local_234[0x4d]) + *(double *)(local_234[0x3d] + 0x58);
      puVar3 = (undefined4 *)FUN_00444d50(local_438,local_234[0x3d] + 0x20,local_234[0x4e]);
      puVar7 = local_190;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar7 = puVar7 + 1;
      }
      puVar3 = local_190;
      puVar7 = (undefined4 *)(local_234[0x3d] + 0x20);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    else {
      fVar8 = (float10)FUN_004428b0();
      local_26c = (float)fVar8;
      local_24c = local_26c * local_23c;
      *(double *)(local_234[0x3d] + 0x48) =
           *(double *)(local_234[0x3d] + 0x48) - (double)(local_24c * local_1f4);
      *(double *)(local_234[0x3d] + 0x50) =
           *(double *)(local_234[0x3d] + 0x50) - (double)(local_24c * local_1f0);
      *(double *)(local_234[0x3d] + 0x58) =
           *(double *)(local_234[0x3d] + 0x58) - (double)(local_24c * local_1ec);
      local_23c = 0.0;
    }
    if ((local_238[1] == 0) || ((float)local_238[2] == 0.0)) {
      if ((float)local_234[0x47] <= 0.0001) {
        local_240 = 1.0;
      }
      else {
        fVar8 = (float10)FUN_004428b0();
        local_288 = (float)fVar8;
        local_240 = 1.0 - local_288 * (float)local_234[0x48] * 0.75 *
                          local_288 * (float)local_234[0x48];
      }
      fVar8 = (float10)FUN_004428b0(&local_1f4,local_238 + 0x18);
      local_28c = (float)fVar8;
      local_280 = local_28c;
      fVar8 = (float10)FUN_004428b0(&local_1f4,&local_1e8);
      local_290 = (float)fVar8;
      piVar5 = (int *)FUN_00439d00(local_37c,local_1e8,local_1e4,local_1e0,local_280 - local_290);
      local_1e8 = *piVar5;
      local_1e4 = (float)piVar5[1];
      local_1e0 = piVar5[2];
      local_80 = local_1e8;
      local_7c = local_1e4;
      local_78 = local_1e0;
      fVar8 = (float10)FUN_004428b0();
      local_254 = (float)fVar8;
      if (0.0001 < local_254) {
        local_240 = (1.0 - (local_1e4 * 0.9 * local_1e4) / local_254) * local_240;
      }
      iVar6 = FUN_00822d90();
      local_248 = iVar6 - local_234[0xa1];
      if (local_248 < 100) {
        local_240 = 1.0;
      }
      else if (local_248 < 500) {
        local_258 = local_248 - 100;
        local_298 = (double)local_258 + (double)(&DAT_008a2fd0)[-(local_258 >> 0x1f)];
        local_240 = 1.0 - ((1.0 - local_240) * (float)local_298) / 400.0;
      }
      piVar5 = (int *)FUN_004462d0(local_394,local_240);
      local_1e8 = *piVar5;
      local_1e4 = (float)piVar5[1];
      local_1e0 = piVar5[2];
      local_d4 = local_1e8;
      local_d0 = (int)local_1e4;
      local_cc = local_1e0;
      fVar8 = (float10)FUN_004428b0();
      local_274 = (float)fVar8;
      if ((25.0 < local_274) && (local_238[1] == 0)) {
        FUN_008245f0(local_234[0x3d],0);
      }
      iVar6 = FUN_00442850();
      if (iVar6 == 0) {
        piVar5 = (int *)FUN_00440300();
        local_200 = *piVar5;
        local_1fc = piVar5[1];
        local_1f8 = piVar5[2];
        local_98 = local_200;
        local_94 = local_1fc;
        local_90 = local_1f8;
        puVar3 = (undefined4 *)FUN_004440d0();
        local_218 = *puVar3;
        local_214 = puVar3[1];
        local_210 = puVar3[2];
        fVar8 = (float10)FUN_004428b0(&local_14,&local_14);
        local_284 = (float)fVar8;
        pfVar4 = (float *)FUN_004462d0(local_358,0.2 / local_284);
        local_1dc = *pfVar4;
        local_1d8 = pfVar4[1];
        local_1d4 = pfVar4[2];
        local_104 = local_1dc;
        local_100 = local_1d8;
        local_fc = local_1d4;
      }
    }
    else {
      local_260 = (float)local_234[0x45];
      local_268 = (float)local_238[2];
      local_200 = local_238[8];
      local_1fc = local_238[9];
      local_1f8 = local_238[10];
      puVar3 = (undefined4 *)
               FUN_00459570(local_2e0,local_260,local_1e8,local_1e4,local_1e0,local_268);
      local_224 = *puVar3;
      local_220 = puVar3[1];
      local_21c = puVar3[2];
      puVar3 = (undefined4 *)FUN_004462d0(local_3a0,1.0 / (local_260 + local_268));
      local_20c = *puVar3;
      local_208 = puVar3[1];
      local_204 = puVar3[2];
      local_38 = local_20c;
      local_34 = local_208;
      local_30 = local_204;
      piVar5 = (int *)FUN_004401a0(local_2f8,local_1e8,local_1e4,local_1e0);
      local_1e8 = *piVar5;
      local_1e4 = (float)piVar5[1];
      local_1e0 = piVar5[2];
      local_44 = local_1e8;
      local_40 = (int)local_1e4;
      local_3c = local_1e0;
      fVar8 = (float10)FUN_004428b0(&local_1f4,&local_1e8);
      local_27c = (float)fVar8;
      piVar5 = (int *)FUN_00459570(local_370,0x3f000000,local_1e8,local_1e4,local_1e0,-local_27c);
      local_1e8 = *piVar5;
      local_1e4 = (float)piVar5[1];
      local_1e0 = piVar5[2];
      local_b0 = local_1e8;
      local_ac = (int)local_1e4;
      local_a8 = local_1e0;
      fVar8 = (float10)FUN_004428b0();
      local_270 = (float)fVar8;
      if (local_270 < 25.0) {
        piVar5 = (int *)FUN_004462d0(local_310,0x40a00000);
        local_1e8 = *piVar5;
        local_1e4 = (float)piVar5[1];
        local_1e0 = piVar5[2];
        local_20 = local_1e8;
        local_1c = (int)local_1e4;
        local_18 = local_1e0;
      }
      piVar5 = (int *)FUN_00440130(local_3b8,local_1e8,local_1e4,local_1e0);
      local_1e8 = *piVar5;
      local_1e4 = (float)piVar5[1];
      local_1e0 = piVar5[2];
      local_2c = local_1e8;
      local_28 = (int)local_1e4;
      local_24 = local_1e0;
      iVar6 = FUN_00442850();
      if (iVar6 == 0) {
        piVar5 = (int *)FUN_00440300();
        local_200 = *piVar5;
        local_1fc = piVar5[1];
        local_1f8 = piVar5[2];
        local_50 = local_200;
        local_4c = local_1fc;
        local_48 = local_1f8;
        puVar3 = (undefined4 *)FUN_004440d0();
        local_230 = *puVar3;
        local_22c = puVar3[1];
        local_228 = puVar3[2];
        fVar8 = (float10)FUN_004428b0(&local_14,&local_14);
        local_278 = (float)fVar8;
        pfVar4 = (float *)FUN_004462d0(local_340,0.2 / local_278);
        local_1dc = *pfVar4;
        local_1d8 = pfVar4[1];
        local_1d4 = pfVar4[2];
        local_5c = local_1dc;
        local_58 = local_1d8;
        local_54 = local_1d4;
      }
    }
    if ((*(uint *)(local_234[0x8c] + 0x114) & 0x200) == 0) {
      if (local_1dc <= 1.5707964) {
        if (local_1dc < -1.5707964) {
          pfVar4 = (float *)FUN_004462d0(local_2bc,-1.5707964 / local_1dc);
          local_1dc = *pfVar4;
          local_1d8 = pfVar4[1];
          local_1d4 = pfVar4[2];
          local_8c = local_1dc;
          local_88 = local_1d8;
          local_84 = local_1d4;
        }
      }
      else {
        pfVar4 = (float *)FUN_004462d0(local_2b0,1.5707964 / local_1dc);
        local_1dc = *pfVar4;
        local_1d8 = pfVar4[1];
        local_1d4 = pfVar4[2];
        local_74 = local_1dc;
        local_70 = local_1d8;
        local_6c = local_1d4;
      }
      if (local_1d8 <= 3.1415927) {
        if (local_1d8 < -3.1415927) {
          pfVar4 = (float *)FUN_004462d0(local_2ec,-3.1415927 / local_1d8);
          local_1dc = *pfVar4;
          local_1d8 = pfVar4[1];
          local_1d4 = pfVar4[2];
          local_c8 = local_1dc;
          local_c4 = local_1d8;
          local_c0 = local_1d4;
        }
      }
      else {
        pfVar4 = (float *)FUN_004462d0(local_2d4,3.1415927 / local_1d8);
        local_1dc = *pfVar4;
        local_1d8 = pfVar4[1];
        local_1d4 = pfVar4[2];
        local_a4 = local_1dc;
        local_a0 = local_1d8;
        local_9c = local_1d4;
      }
      if (local_1d4 <= 0.7853982) {
        if (local_1d4 < -0.7853982) {
          pfVar4 = (float *)FUN_004462d0(local_31c,-0.7853982 / local_1d4);
          local_1dc = *pfVar4;
          local_1d8 = pfVar4[1];
          local_1d4 = pfVar4[2];
          local_f8 = local_1dc;
          local_f4 = local_1d8;
          local_f0 = local_1d4;
        }
      }
      else {
        pfVar4 = (float *)FUN_004462d0(local_304,0.7853982 / local_1d4);
        local_1dc = *pfVar4;
        local_1d8 = pfVar4[1];
        local_1d4 = pfVar4[2];
        local_e0 = local_1dc;
        local_dc = local_1d8;
        local_d8 = local_1d4;
      }
      piVar5 = (int *)FUN_00440130(local_334,local_234[0x4e],local_234[0x4f],local_234[0x50]);
      local_110 = *piVar5;
      local_10c = piVar5[1];
      local_108 = piVar5[2];
      local_234[0x4e] = local_110;
      local_234[0x4f] = local_10c;
      local_234[0x50] = local_108;
    }
    fVar8 = (float10)FUN_004428b0();
    local_264 = (float)fVar8;
    if (local_264 < 0.0) {
      piVar5 = (int *)FUN_00439d00(local_34c,local_234[0x51],local_234[0x52],local_234[0x53],
                                   -local_264);
      local_bc = *piVar5;
      local_b8 = piVar5[1];
      local_b4 = piVar5[2];
      local_234[0x51] = local_bc;
      local_234[0x52] = local_b8;
      local_234[0x53] = local_b4;
    }
    local_234[0x4b] = local_1e8;
    local_234[0x4c] = (int)local_1e4;
    local_234[0x4d] = local_1e0;
    fVar8 = (float10)FUN_0045c420();
    local_244 = (float)fVar8;
    local_234[0x47] = (int)local_244;
    if (local_244 <= 0.0) {
      local_25c = 1e+30;
    }
    else {
      local_25c = 1.0 / local_244;
    }
    local_234[0x48] = (int)local_25c;
    *(double *)(local_234[0x3d] + 0x48) =
         (double)((param_2 - local_23c) * (float)local_234[0x4b]) +
         *(double *)(local_234[0x3d] + 0x48);
    *(double *)(local_234[0x3d] + 0x50) =
         (double)((param_2 - local_23c) * (float)local_234[0x4c]) +
         *(double *)(local_234[0x3d] + 0x50);
    *(double *)(local_234[0x3d] + 0x58) =
         (double)((param_2 - local_23c) * (float)local_234[0x4d]) +
         *(double *)(local_234[0x3d] + 0x58);
    puVar3 = (undefined4 *)FUN_00444d50(local_478,local_234[0x3d] + 0x20,local_234[0x4e]);
    puVar7 = local_150;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar3 = local_150;
    puVar7 = (undefined4 *)(local_234[0x3d] + 0x20);
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    FUN_00442900();
    iVar6 = FUN_00822d90();
    local_234[0xa1] = iVar6;
    if ((*(uint *)(local_234[0x3d] + 0x14) & 0x200) != 0) {
      *(undefined4 *)(local_234[0x8c] + 0x110) = 0;
    }
  }
  FUN_0083e885();
  return;
}

