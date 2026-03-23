
void __thiscall FUN_005cf510(int param_1,float param_2)

{
  float fVar1;
  char cVar2;
  float *pfVar3;
  double *pdVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  float *pfVar9;
  float10 fVar10;
  undefined1 local_4c0 [64];
  undefined1 local_480 [64];
  undefined1 local_440 [24];
  undefined1 local_428 [44];
  undefined1 local_3fc [12];
  undefined1 local_3f0 [12];
  undefined1 local_3e4 [12];
  undefined1 local_3d8 [12];
  undefined1 local_3cc [12];
  undefined1 local_3c0 [12];
  undefined1 local_3b4 [12];
  undefined1 local_3a8 [12];
  undefined1 local_39c [12];
  undefined1 local_390 [12];
  undefined1 local_384 [12];
  undefined1 local_378 [12];
  undefined1 local_36c [12];
  undefined1 local_360 [12];
  undefined1 local_354 [12];
  undefined1 local_348 [12];
  undefined8 local_33c;
  undefined8 local_334;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  float local_320;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  float local_310;
  undefined4 *local_30c;
  float local_308;
  float local_304;
  float local_300;
  float local_2fc;
  float local_2f8;
  float local_2f4;
  float local_2f0;
  float local_2ec;
  float local_2e8;
  float local_2e4;
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
  undefined4 *local_2b0;
  float local_2ac;
  int local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  ushort *local_298;
  float local_294;
  float local_290;
  float local_28c;
  uint local_288;
  float local_284;
  int local_280;
  int local_27c;
  ushort local_278;
  int local_274;
  float local_270;
  int local_26c;
  short *local_268;
  int local_264;
  float local_260;
  int local_25c;
  int local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  float local_248;
  float local_244;
  float local_240;
  float local_23c;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224 [16];
  undefined4 local_1e4 [16];
  float local_1a4 [5];
  float local_190;
  undefined1 local_18c [16];
  undefined8 local_17c;
  double local_174;
  undefined8 local_16c;
  undefined1 local_164 [12];
  float local_158 [2];
  float local_150;
  double local_14c;
  double local_144;
  double local_13c;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(float *)(param_1 + 0x78) <= param_2 && param_2 != *(float *)(param_1 + 0x78)) {
    param_2 = *(float *)(param_1 + 0x78);
  }
  if (0.0 < *(float *)(param_1 + 0x78)) {
    fVar1 = *(float *)(*(int *)(param_1 + 0xc) + 0x94);
    if (fVar1 < *(float *)(param_1 + 0x78) || fVar1 == *(float *)(param_1 + 0x78)) {
      *(float *)(param_1 + 0xe0) =
           *(float *)(*(int *)(param_1 + 0xc) + 0x90) * param_2 + *(float *)(param_1 + 0xe0);
      if (1.0 < *(float *)(param_1 + 0xe0)) {
        *(undefined4 *)(param_1 + 0xe0) = 0x3f800000;
      }
    }
    else {
      *(float *)(param_1 + 0xe0) =
           *(float *)(param_1 + 0xe0) - *(float *)(*(int *)(param_1 + 0xc) + 0x98) * param_2;
      if (*(float *)(param_1 + 0xe0) <= 0.0 && *(float *)(param_1 + 0xe0) != 0.0) {
        *(undefined4 *)(param_1 + 0xe0) = 0;
      }
    }
  }
  else {
    *(uint *)(*(int *)(param_1 + 0x14) + 0x14) = *(uint *)(*(int *)(param_1 + 0x14) + 0x14) | 0x200;
  }
  local_258 = param_1;
  FUN_005cf3f0();
  pfVar3 = (float *)FUN_004560b0(local_36c,*(int *)(local_258 + 0x14) + 0x20);
  local_74 = *pfVar3;
  local_70 = pfVar3[1];
  local_6c = pfVar3[2];
  local_14 = local_74;
  local_10 = local_70;
  local_c = local_6c;
  pdVar4 = (double *)FUN_00447f60(local_440,*(int *)(local_258 + 0x14) + 0x20);
  local_e0 = *(undefined4 *)pdVar4;
  local_dc = *(undefined4 *)((int)pdVar4 + 4);
  local_d8 = *(undefined4 *)(pdVar4 + 1);
  local_d4 = *(undefined4 *)((int)pdVar4 + 0xc);
  local_24 = pdVar4[1];
  local_d0 = *(undefined4 *)(pdVar4 + 2);
  local_cc = *(undefined4 *)((int)pdVar4 + 0x14);
  local_2c = (double)(param_2 * *(float *)(*(int *)(local_258 + 0xc) + 0x54) * local_14) + *pdVar4;
  local_1c = (double)(param_2 * *(float *)(*(int *)(local_258 + 0xc) + 0x54) * local_c) + pdVar4[2];
  iVar5 = FUN_0077d560(local_2c,local_1c);
  if (iVar5 == 0) {
    *(uint *)(*(int *)(local_258 + 0x14) + 0x14) =
         *(uint *)(*(int *)(local_258 + 0x14) + 0x14) | 0x200;
  }
  else {
    FUN_00785730(SUB84(local_2c,0),(int)((ulonglong)local_2c >> 0x20),SUB84(local_1c,0),
                 (int)((ulonglong)local_1c >> 0x20),&local_2cc,local_164);
    local_24 = (double)local_2cc;
    puVar6 = (undefined4 *)FUN_0081f920(local_480,local_164,&local_14);
    puVar8 = local_1e4;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar6 = local_1e4;
    puVar8 = (undefined4 *)(*(int *)(local_258 + 0x14) + 0x20);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    FUN_0044b7d0(*(int *)(local_258 + 0x14) + 0x20,&local_2c);
    pfVar3 = (float *)FUN_004560b0(local_3b4,*(int *)(local_258 + 0x14) + 0x20);
    local_f8 = *pfVar3;
    local_f4 = pfVar3[1];
    local_f0 = pfVar3[2];
    local_14 = local_f8;
    local_10 = local_f4;
    local_c = local_f0;
    FUN_005cf100();
    local_2fc = (*(float *)(local_258 + 0xe0) * *(float *)(*(int *)(local_258 + 0xc) + 0x84)) / 0.1;
    local_268 = *(short **)(local_258 + 0xf4);
    for (local_280 = *(int *)(local_258 + 0xe8); local_280 <= *(int *)(local_258 + 0xf0);
        local_280 = local_280 + 1) {
      for (local_27c = *(int *)(local_258 + 0xe4); local_27c <= *(int *)(local_258 + 0xec);
          local_27c = local_27c + 1) {
        local_298 = (ushort *)FUN_00492d60(local_27c,local_280);
        local_278 = *local_298;
        local_288 = local_278 & 0xfff;
        local_2a4 = (float)((double)((float)local_27c * DAT_02cc50e0) - local_2c) *
                    *(float *)(*(int *)(local_258 + 0xc) + 0x7c);
        local_29c = (float)((double)((float)local_288 * 0.1) - local_24) *
                    *(float *)(*(int *)(local_258 + 0xc) + 0x7c);
        local_2ac = (float)((double)((float)local_280 * DAT_02cc50e0) - local_1c) *
                    *(float *)(*(int *)(local_258 + 0xc) + 0x7c);
        local_290 = local_2a4 * local_2a4 + local_29c * local_29c + local_2ac * local_2ac;
        if (local_290 < 1.0) {
          fVar10 = (float10)FUN_00417910(local_290);
          local_2d4 = (float)fVar10;
          fVar10 = (float10)FUN_004178b0(local_2d4 * 3.1415927);
          local_2b4 = (float)fVar10;
          local_274 = (int)((local_2b4 * 0.5 + 0.5) * local_2fc) + local_288;
          if (local_274 < 0) {
            local_274 = 0;
          }
          else if (0xfff < local_274) {
            local_274 = 0xfff;
          }
          *local_268 = (short)local_274 - (short)local_288;
          *local_298 = (local_278 & 0xf000) + (short)local_274;
        }
        else {
          *local_268 = 0;
        }
        local_268 = local_268 + 1;
      }
    }
    FUN_00777730(*(undefined4 *)(local_258 + 0xe4),*(undefined4 *)(local_258 + 0xe8),
                 *(undefined4 *)(local_258 + 0xec),*(undefined4 *)(local_258 + 0xf0));
    puVar6 = (undefined4 *)FUN_004795e0(local_3e4,*(int *)(local_258 + 0x14) + 0x20);
    local_254 = *puVar6;
    local_250 = puVar6[1];
    local_24c = puVar6[2];
    local_14c = (double)(local_14 * *(float *)(*(int *)(local_258 + 0xc) + 0x78) * 0.5) + local_2c;
    local_144 = (double)(local_10 * *(float *)(*(int *)(local_258 + 0xc) + 0x78) * 0.5) + local_24;
    local_13c = (double)(local_c * *(float *)(*(int *)(local_258 + 0xc) + 0x78) * 0.5) + local_1c;
    local_284 = param_2;
    if (0.2 < param_2) {
      local_284 = 0.2;
    }
    local_8c = local_254;
    local_88 = local_250;
    local_84 = local_24c;
    fVar10 = (float10)FUN_00822d80();
    local_304 = (float)fVar10;
    local_2d0 = local_304 * *(float *)(*(int *)(local_258 + 0xc) + 0xa4);
    FUN_005b28e0(SUB84(local_14c,0),(int)((ulonglong)local_14c >> 0x20),SUB84(local_13c,0),
                 (int)((ulonglong)local_13c >> 0x20),
                 (double)*(float *)(*(int *)(local_258 + 0xc) + 0x78) * 1.5 + 20.0,local_428);
LAB_005cfd63:
    cVar2 = FUN_00462710(&local_30c);
    if (cVar2 != '\0') {
      local_25c = FUN_004da060(*local_30c);
      if (local_25c != 0) {
        local_26c = FUN_0045c4d0();
        local_248 = (float)(local_14c - *(double *)(local_26c + 0x28));
        local_244 = (float)(local_144 - *(double *)(local_26c + 0x30));
        local_240 = (float)(local_13c - *(double *)(local_26c + 0x38));
        fVar10 = (float10)FUN_004428b0(&local_248,&local_254,local_254,local_250,local_24c);
        local_2f0 = (float)fVar10;
        pfVar3 = (float *)FUN_00439d00(local_354,local_248,local_244,local_240,local_2f0 * 2.0);
        local_248 = *pfVar3;
        local_244 = pfVar3[1];
        local_240 = pfVar3[2];
        local_c8 = local_248;
        local_c4 = local_244;
        local_c0 = local_240;
        fVar10 = (float10)FUN_004428b0(&local_248,&local_248);
        local_2a0 = (float)fVar10;
        local_2e0 = *(float *)(*(int *)(local_258 + 0xc) + 0x78) * 1.5;
        iVar5 = FUN_00462400();
        local_28c = local_2e0 + *(float *)(iVar5 + 0xc);
        if (local_2a0 <= local_28c * local_28c) {
          local_2ec = *(float *)(local_258 + 0xe0) * local_284;
          fVar10 = (float10)FUN_005ce850(*(float *)(*(int *)(local_258 + 0xc) + 0x80) * local_2a0);
          local_308 = (float)fVar10;
          local_260 = local_2ec * local_308;
          iVar5 = (*(code *)**(undefined4 **)(local_25c + 0x18))();
          local_264 = *(int *)(iVar5 + 0x1c);
          if (((local_264 == 1) || (local_264 == 6)) || (local_264 == 3)) {
            local_31c = *(undefined4 *)(local_258 + 0x60);
            local_318 = *(undefined4 *)(local_258 + 100);
            local_314 = *(undefined4 *)(local_258 + 0x68);
            local_310 = *(float *)(local_258 + 0x6c) * local_260;
            pfVar3 = (float *)FUN_00785430(local_348,(int)*(undefined8 *)(local_26c + 0x28),
                                           (int)((ulonglong)*(undefined8 *)(local_26c + 0x28) >>
                                                0x20),(int)*(undefined8 *)(local_26c + 0x38),
                                           (int)((ulonglong)*(undefined8 *)(local_26c + 0x38) >>
                                                0x20));
            local_a4 = *pfVar3;
            local_a0 = pfVar3[1];
            local_9c = pfVar3[2];
            local_23c = local_14 + local_a4;
            local_238 = local_10 + local_a0 + 1.0;
            local_234 = local_c + local_9c;
            local_44 = local_a4;
            local_40 = local_a0;
            local_3c = local_9c;
            pfVar3 = (float *)FUN_004621a0(local_384,&local_23c);
            local_23c = *pfVar3;
            local_238 = pfVar3[1];
            local_234 = pfVar3[2];
            local_ec = local_23c;
            local_e8 = local_238;
            local_e4 = local_234;
            (**(code **)(*(int *)(local_25c + 0x18) + 0x38))(&local_31c,&local_23c);
            iVar5 = FUN_00462450();
            local_270 = (float)iVar5 + local_2d0;
            pfVar3 = (float *)FUN_004462d0(local_3fc,
                                           *(float *)(*(int *)(local_258 + 0xc) + 0x9c) * local_260,
                                           local_23c,local_238,local_234);
            local_230 = *pfVar3;
            local_22c = pfVar3[1];
            local_228 = pfVar3[2];
            local_bc = local_230;
            local_b8 = local_22c;
            local_b4 = local_228;
            pfVar3 = (float *)FUN_004440d0(local_3f0,&local_44,&local_230);
            local_230 = *pfVar3;
            local_22c = pfVar3[1];
            local_228 = pfVar3[2];
            local_104 = local_230;
            local_100 = local_22c;
            local_fc = local_228;
            pfVar3 = (float *)FUN_00440300(local_3d8,&local_230,local_26c);
            local_230 = *pfVar3;
            local_22c = pfVar3[1];
            local_228 = pfVar3[2];
            local_11c = local_230;
            local_118 = local_22c;
            local_114 = local_228;
            fVar10 = (float10)FUN_00822970(local_270 + 8.53);
            local_300 = (float)fVar10;
            local_230 = local_300 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xa8) +
                        local_230;
            fVar10 = (float10)FUN_00822970(local_270 + 17.67);
            local_2d8 = (float)fVar10;
            local_22c = local_2d8 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xa8) * 0.5 +
                        local_22c;
            fVar10 = (float10)FUN_00822970(local_270 + 5.19);
            local_2f8 = (float)fVar10;
            local_228 = local_2f8 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xa8) +
                        local_228;
            iVar5 = (*(code *)**(undefined4 **)(local_25c + 0x18))();
            local_2a8 = *(int *)(iVar5 + 0x14);
            if (local_2a8 == 0x54555252) {
              pfVar3 = (float *)FUN_004462d0(local_360,
                                             *(undefined4 *)(*(int *)(local_258 + 0xc) + 0xb4),
                                             local_230,local_22c,local_228);
              local_230 = *pfVar3;
              local_22c = pfVar3[1];
              local_228 = pfVar3[2];
              local_50 = local_230;
              local_4c = local_22c;
              local_48 = local_228;
            }
            else if (local_2a8 == 0x57414c4b) {
              pfVar3 = (float *)FUN_004462d0(local_3cc,
                                             *(undefined4 *)(*(int *)(local_258 + 0xc) + 0xb0),
                                             local_230,local_22c,local_228);
              local_230 = *pfVar3;
              local_22c = pfVar3[1];
              local_228 = pfVar3[2];
              local_110 = local_230;
              local_10c = local_22c;
              local_108 = local_228;
            }
            iVar5 = FUN_0045c490();
            pfVar3 = (float *)FUN_00439d00(local_378,local_230,local_22c,local_228,
                                           -*(float *)(*(int *)(local_258 + 0xc) + 0xb8) * local_260
                                           ,*(undefined4 *)(iVar5 + 0x24),
                                           *(undefined4 *)(iVar5 + 0x28),
                                           *(undefined4 *)(iVar5 + 0x2c));
            local_230 = *pfVar3;
            local_22c = pfVar3[1];
            local_228 = pfVar3[2];
            local_5c = local_230;
            local_58 = local_22c;
            local_54 = local_228;
            uVar7 = FUN_0045c4d0();
            puVar6 = (undefined4 *)FUN_004560b0(local_39c,uVar7);
            local_128 = *puVar6;
            local_124 = puVar6[1];
            local_120 = puVar6[2];
            local_68 = local_128;
            local_64 = local_124;
            local_60 = local_120;
            uVar7 = FUN_0045c4d0();
            puVar6 = (undefined4 *)FUN_00439d80(local_390,uVar7);
            local_134 = *puVar6;
            local_130 = puVar6[1];
            local_12c = puVar6[2];
            local_2dc = *(float *)(*(int *)(local_258 + 0xc) + 0xbc) * local_260;
            local_80 = local_134;
            local_7c = local_130;
            local_78 = local_12c;
            fVar10 = (float10)FUN_004428b0(&local_44,&local_128);
            local_2e8 = (float)fVar10;
            local_230 = local_230 - local_2dc * local_2e8;
            local_2b8 = *(float *)(*(int *)(local_258 + 0xc) + 0xbc) * local_260;
            fVar10 = (float10)FUN_004428b0(&local_44,&local_134);
            local_2bc = (float)fVar10;
            local_228 = local_2b8 * local_2bc + local_228;
            iVar5 = FUN_0045c490();
            local_2b0 = (undefined4 *)(iVar5 + 0x24);
            puVar6 = (undefined4 *)
                     FUN_00440130(local_3a8,*local_2b0,*(undefined4 *)(iVar5 + 0x28),
                                  *(undefined4 *)(iVar5 + 0x2c),local_230,local_22c,local_228);
            local_98 = *puVar6;
            local_94 = puVar6[1];
            local_90 = puVar6[2];
            *local_2b0 = local_98;
            local_2b0[1] = local_94;
            local_2b0[2] = local_90;
            pfVar3 = (float *)FUN_004462d0(local_3c0,
                                           *(float *)(*(int *)(local_258 + 0xc) + 0xa0) * local_260,
                                           local_23c,local_238,local_234);
            local_b0 = *pfVar3;
            local_ac = pfVar3[1];
            local_a8 = pfVar3[2];
            local_38 = local_b0;
            local_34 = local_ac;
            local_30 = local_a8;
            fVar10 = (float10)FUN_00822970(local_270);
            local_2c4 = (float)fVar10;
            local_38 = local_2c4 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xac) +
                       local_38;
            fVar10 = (float10)FUN_00822970(local_270 + 2.27);
            local_2e4 = (float)fVar10;
            local_34 = local_2e4 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xac) * 0.5 +
                       local_34;
            fVar10 = (float10)FUN_00822970(local_270 + 23.41);
            local_2c0 = (float)fVar10;
            local_30 = local_2c0 * local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xac) +
                       local_30;
            FUN_004a75b0(&local_38);
          }
          else if (((local_264 == 2) || (local_264 == 10)) || ((local_264 == 7 || (local_264 == 5)))
                  ) {
            local_260 = local_260 * *(float *)(*(int *)(local_258 + 0xc) + 0xc0);
            local_32c = *(undefined4 *)(local_258 + 0x60);
            local_328 = *(undefined4 *)(local_258 + 100);
            local_324 = *(undefined4 *)(local_258 + 0x68);
            local_320 = *(float *)(local_258 + 0x6c) * local_260;
            (**(code **)(*(int *)(local_25c + 0x18) + 0x38))(&local_32c,local_164);
            pfVar3 = (float *)FUN_0045c4d0();
            pfVar9 = local_1a4;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar9 = *pfVar3;
              pfVar3 = pfVar3 + 1;
              pfVar9 = pfVar9 + 1;
            }
            local_33c = local_17c;
            local_334 = local_16c;
            FUN_00785730((int)local_17c,(int)((ulonglong)local_17c >> 0x20),(int)local_16c,
                         (int)((ulonglong)local_16c >> 0x20),&local_294,local_158);
            if (ABS(local_174 - (double)local_294) <= 0.009999999776482582) {
              fVar10 = (float10)FUN_00453f80(local_1a4[3] - local_158[0]);
              local_2f4 = (float)fVar10;
              if (local_2f4 <= 0.001) {
                fVar10 = (float10)FUN_00453f80(local_190 - local_150);
                local_2c8 = (float)fVar10;
                if (local_2c8 <= 0.001) goto LAB_005cfd63;
              }
            }
            pfVar3 = (float *)FUN_0081f920(local_4c0,local_158,local_18c);
            pfVar9 = local_224;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar9 = *pfVar3;
              pfVar3 = pfVar3 + 1;
              pfVar9 = pfVar9 + 1;
            }
            pfVar3 = local_224;
            pfVar9 = local_1a4;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar9 = *pfVar3;
              pfVar3 = pfVar3 + 1;
              pfVar9 = pfVar9 + 1;
            }
            local_17c = local_33c;
            local_174 = (double)local_294;
            local_16c = local_334;
            FUN_0056d6a0(local_1a4);
            pfVar3 = local_1a4;
            pfVar9 = (float *)(local_25c + 0x28);
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar9 = *pfVar3;
              pfVar3 = pfVar3 + 1;
              pfVar9 = pfVar9 + 1;
            }
            uVar7 = (**(code **)(*(int *)(local_25c + 0x18) + 0x30))();
            iVar5 = FUN_00445220(uVar7);
            if (iVar5 != 0) {
              uVar7 = (**(code **)(*(int *)(local_25c + 0x18) + 0x2c))();
              std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
                        (uVar7);
              uVar7 = (**(code **)(*(int *)(local_25c + 0x18) + 0x2c))();
              FUN_00434910(uVar7);
            }
          }
        }
      }
      goto LAB_005cfd63;
    }
    *(float *)(local_258 + 0x78) = *(float *)(local_258 + 0x78) - param_2;
  }
  FUN_0083e885();
  return;
}

