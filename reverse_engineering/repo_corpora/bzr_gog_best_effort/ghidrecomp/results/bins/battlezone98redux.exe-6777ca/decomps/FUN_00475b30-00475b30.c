
void __fastcall FUN_00475b30(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  double *pdVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float10 fVar9;
  undefined1 local_43c [64];
  undefined1 local_3fc [24];
  undefined1 local_3e4 [24];
  undefined1 local_3cc [24];
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
  undefined1 local_33c [12];
  undefined1 local_330 [12];
  undefined1 local_324 [12];
  undefined1 local_318 [12];
  undefined1 local_30c [12];
  undefined1 local_300 [4];
  undefined1 local_2fc [4];
  float local_2f8;
  undefined4 local_2f4;
  undefined4 local_2f0;
  float local_2ec;
  float local_2e8;
  float local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  float local_2d4;
  float local_2d0;
  undefined4 local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  float local_298;
  float local_294;
  undefined4 local_290;
  float local_28c;
  int *local_288;
  float local_284;
  int local_280;
  float *local_27c;
  int local_278;
  float local_274;
  int local_270;
  int local_26c;
  char local_265;
  float local_264;
  int *local_260;
  char local_259;
  int *local_258;
  int local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
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
  undefined4 local_200;
  undefined4 local_1fc [16];
  undefined4 local_1bc [16];
  undefined1 local_17c [12];
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
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
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  float local_98;
  float local_94;
  float local_90;
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
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_254 = param_1;
  (**(code **)(**(int **)(param_1 + 0x34) + 0x88))(0);
  local_260 = (int *)FUN_00462630();
  if (local_260 == (int *)0x0) {
    FUN_005f91e0(*(undefined4 *)(local_254 + 0x34),0x18,
                 *(undefined4 *)(*(int *)(local_254 + 0x34) + 0xb0));
    if (*(int *)(*(int *)(local_254 + 0x34) + 0xac) == 4) {
      FUN_004dbc00();
    }
    *(undefined4 *)(local_254 + 0x20) = 3;
    goto LAB_00476f79;
  }
  local_2f4 = FUN_00417ca0();
  iVar3 = FUN_00417ca0();
  if ((iVar3 == 0) || (cVar2 = FUN_004db510(), cVar2 != '\0')) {
    *(undefined4 *)(local_254 + 0x20) = 3;
    goto LAB_00476f79;
  }
  iVar3 = FUN_00462550();
  if (*(int *)(local_254 + 0x3c) == iVar3) {
    fVar9 = (float10)FUN_00822d80();
    local_2a8 = (float)fVar9;
    local_2a0 = local_2a8;
    fVar9 = (float10)FUN_00462570();
    local_2b0 = (float)fVar9;
    if (local_2a8 - local_2b0 < 5.0) {
      fVar9 = (float10)FUN_00822d80();
      local_2c0 = (float)fVar9;
      *(float *)(local_254 + 0x7c) = local_2c0 + 30.0;
    }
  }
  iVar3 = FUN_00462530();
  iVar4 = FUN_00462380();
  if (iVar3 == iVar4) {
    fVar9 = (float10)FUN_00822d80();
    local_2d0 = (float)fVar9;
    local_2c8 = local_2d0;
    fVar9 = (float10)FUN_0046d040();
    local_2d8 = (float)fVar9;
    if (local_2d0 - local_2d8 < 5.0) {
      fVar9 = (float10)FUN_00822d80();
      local_2e4 = (float)fVar9;
      *(float *)(local_254 + 0x7c) = local_2e4 + 30.0;
    }
  }
  fVar9 = (float10)FUN_00822d80();
  local_2ec = (float)fVar9;
  if (*(float *)(local_254 + 0x7c) <= local_2ec && local_2ec != *(float *)(local_254 + 0x7c)) {
    FUN_005f91e0(*(undefined4 *)(local_254 + 0x34),0x13,0);
    *(undefined4 *)(local_254 + 0x20) = 3;
    goto LAB_00476f79;
  }
  local_258 = (int *)0x0;
  local_278 = 0;
  while ((piVar1 = local_258, local_278 < 5 &&
         (local_288 = (int *)FUN_00417f60(), piVar1 = local_288, local_288 == (int *)0x0))) {
    local_278 = local_278 + 1;
  }
  local_258 = piVar1;
  (**(code **)(local_260[6] + 0x30))();
  iVar3 = FUN_0062e000();
  if (iVar3 == 0) {
LAB_00475e6d:
    local_290 = 0;
  }
  else {
    (**(code **)(local_260[6] + 0x30))();
    iVar3 = FUN_00417e20();
    if ((iVar3 != 0) && (cVar2 = (**(code **)(*local_260 + 0x6c))(), cVar2 == '\0'))
    goto LAB_00475e6d;
    local_290 = 1;
  }
  local_265 = (char)local_290;
  local_259 = '\x01';
  local_27c = (float *)(*(int *)(*(int *)(local_254 + 0x34) + 0x230) + 0xc4);
  puVar5 = (undefined4 *)FUN_0081fe60(local_43c,local_258[4] + 0x20,local_258 + 10);
  puVar8 = local_1fc;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar5 = local_1fc;
  puVar8 = local_1bc;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  local_270 = 0;
  if (*(int *)(local_258[2] + 0xc) == 0x4d4f5254) {
    if ((local_259 != '\0') &&
       (cVar2 = FUN_00462b60(*(undefined4 *)(local_254 + 0x34),*(undefined4 *)(local_254 + 0x68),
                             0x3e99999a,0x3f800000), cVar2 != '\0')) {
      local_259 = '\0';
    }
    cVar2 = FUN_0056b1c0(&local_214,local_2fc,local_260,local_259);
    if (cVar2 == '\0') {
      FUN_005f91e0(*(undefined4 *)(local_254 + 0x34),0x13,0);
      *(undefined4 *)(local_254 + 0x20) = 3;
      goto LAB_00476f79;
    }
    puVar5 = (undefined4 *)FUN_00439de0(local_384,local_258 + 10);
    local_250 = *puVar5;
    local_24c = puVar5[1];
    local_248 = puVar5[2];
    puVar5 = (undefined4 *)
             FUN_004401a0(local_39c,local_214,local_210,local_20c,local_250,local_24c,local_248);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_74 = local_208;
    local_70 = local_204;
    local_6c = local_200;
    puVar5 = (undefined4 *)FUN_004621a0(local_360,&local_208);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_a4 = local_208;
    local_a0 = local_204;
    local_9c = local_200;
    fVar9 = (float10)FUN_00417910();
    local_274 = (float)fVar9;
    pdVar6 = (double *)FUN_00447f60(local_3cc,local_1bc);
    local_e0 = *(undefined4 *)pdVar6;
    local_dc = *(undefined4 *)((int)pdVar6 + 4);
    local_20 = *pdVar6;
    local_d8 = *(undefined4 *)(pdVar6 + 1);
    local_d4 = *(undefined4 *)((int)pdVar6 + 0xc);
    local_18 = pdVar6[1];
    local_d0 = *(undefined4 *)(pdVar6 + 2);
    local_cc = *(undefined4 *)((int)pdVar6 + 0x14);
    local_10 = pdVar6[2];
    local_38 = local_e0;
    uStack_34 = local_dc;
    local_30 = local_d8;
    uStack_2c = local_d4;
    local_28 = local_d0;
    uStack_24 = local_cc;
    pfVar7 = (float *)FUN_004462d0(local_30c,*(undefined4 *)(local_258[3] + 0x54),local_208,
                                   local_204,local_200);
    local_bc = *pfVar7;
    local_b8 = pfVar7[1];
    local_b4 = pfVar7[2];
    local_44 = local_bc;
    local_40 = local_b8;
    local_3c = local_b4;
    for (; 0.0 < local_274; local_274 = local_274 - local_264) {
      fVar9 = (float10)FUN_00456080(local_274,0x3f800000);
      local_2e0 = (float)fVar9;
      local_40 = local_40 - local_2e0 * 0.5 * 9.8;
      local_20 = (double)(local_2e0 * local_44) + local_20;
      local_18 = (double)(local_2e0 * local_40) + local_18;
      local_10 = (double)(local_2e0 * local_3c) + local_10;
      local_40 = local_40 - local_2e0 * 0.5 * 9.8;
      local_98 = (float)(local_20 - (double)CONCAT44(uStack_34,local_38));
      local_94 = (float)(local_18 - (double)CONCAT44(uStack_2c,local_30));
      local_90 = (float)(local_10 - (double)CONCAT44(uStack_24,local_28));
      local_264 = local_2e0;
      iVar3 = FUN_00784620(local_38,uStack_34,local_30,uStack_2c,local_28,uStack_24,local_98,
                           local_94,local_90,&local_2e0);
      if (iVar3 != 0) {
        local_270 = 1;
        break;
      }
      local_38 = (undefined4)local_20;
      uStack_34 = local_20._4_4_;
      local_30 = (undefined4)local_18;
      uStack_2c = local_18._4_4_;
      local_28 = (undefined4)local_10;
      uStack_24 = local_10._4_4_;
    }
  }
  else {
    puVar5 = (undefined4 *)(**(code **)(*local_258 + 0x2c))(local_17c,local_260);
    local_214 = *puVar5;
    local_210 = puVar5[1];
    local_20c = puVar5[2];
    puVar5 = (undefined4 *)FUN_00439de0(local_318,local_258 + 10);
    local_22c = *puVar5;
    local_228 = puVar5[1];
    local_224 = puVar5[2];
    puVar5 = (undefined4 *)
             FUN_004401a0(local_324,local_214,local_210,local_20c,local_22c,local_228,local_224);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_2f0 = 0x3f800000;
    local_ec = local_208;
    local_e8 = local_204;
    local_e4 = local_200;
    puVar5 = (undefined4 *)FUN_00447f60(local_3fc,local_258 + 10);
    local_134 = *puVar5;
    local_130 = puVar5[1];
    local_12c = puVar5[2];
    local_128 = puVar5[3];
    local_124 = puVar5[4];
    local_120 = puVar5[5];
    local_104 = local_134;
    local_100 = local_130;
    local_fc = local_12c;
    local_f8 = local_128;
    local_f4 = local_124;
    local_f0 = local_120;
    local_270 = FUN_00784620(local_134,local_130,local_12c,local_128,local_124,local_120,local_208,
                             local_204,local_200,&local_2f0,0);
    puVar5 = (undefined4 *)FUN_004621a0(local_33c,&local_208);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_b0 = local_208;
    local_ac = local_204;
    local_a8 = local_200;
  }
  if (((*(int *)(local_258[2] + 0xc) == 0x4d4f5254) && (local_259 != '\0')) && (local_270 != 0)) {
    cVar2 = FUN_0056b1c0(&local_214,local_300,local_260,0);
    if (cVar2 == '\0') {
      FUN_005f91e0(*(undefined4 *)(local_254 + 0x34),0x13,0);
      *(undefined4 *)(local_254 + 0x20) = 3;
      goto LAB_00476f79;
    }
    puVar5 = (undefined4 *)FUN_00439de0(local_354,local_258 + 10);
    local_244 = *puVar5;
    local_240 = puVar5[1];
    local_23c = puVar5[2];
    puVar5 = (undefined4 *)
             FUN_004401a0(local_3b4,local_214,local_210,local_20c,local_244,local_240,local_23c);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_2cc = 0x3f800000;
    local_140 = local_208;
    local_13c = local_204;
    local_138 = local_200;
    puVar5 = (undefined4 *)FUN_00447f60(local_3e4,local_258 + 10);
    local_158 = *puVar5;
    local_154 = puVar5[1];
    local_150 = puVar5[2];
    local_14c = puVar5[3];
    local_148 = puVar5[4];
    local_144 = puVar5[5];
    local_11c = local_158;
    local_118 = local_154;
    local_114 = local_150;
    local_110 = local_14c;
    local_10c = local_148;
    local_108 = local_144;
    local_270 = FUN_00784620(local_158,local_154,local_150,local_14c,local_148,local_144,local_208,
                             local_204,local_200,&local_2cc,0);
    puVar5 = (undefined4 *)FUN_004621a0(local_378,&local_208);
    local_208 = *puVar5;
    local_204 = puVar5[1];
    local_200 = puVar5[2];
    local_c8 = local_208;
    local_c4 = local_204;
    local_c0 = local_200;
  }
  pfVar7 = (float *)FUN_00440300(local_3a8,&local_208,local_1bc);
  local_5c = *pfVar7;
  local_58 = pfVar7[1];
  local_54 = pfVar7[2];
  local_50 = local_5c;
  local_4c = local_58;
  local_48 = local_54;
  fVar9 = (float10)FUN_00447ed0(local_5c * -2.5,0xbf800000,0x3f800000);
  *local_27c = (float)fVar9;
  fVar9 = (float10)FUN_00447ed0(local_4c * 2.5,0xbf800000,0x3f800000);
  local_2bc = (float)fVar9;
  local_294 = local_2bc * 2.0;
  fVar9 = (float10)FUN_00822d60();
  local_2b8 = (float)fVar9;
  local_27c[1] = local_294 * local_2b8 + local_27c[1];
  if ((local_258[3] == 0) || (*(int *)(local_258[3] + 0xc) != 0x504f5052)) {
    if ((*(int *)(local_258[2] + 0xc) == 0x52444554) && (cVar2 = FUN_004757d0(), cVar2 != '\0')) {
      local_26c = FUN_004757f0();
      if (local_26c != 0) {
        puVar5 = (undefined4 *)FUN_00439de0(local_330,*(int *)(local_26c + 0x14) + 0x20);
        local_238 = *puVar5;
        local_234 = puVar5[1];
        local_230 = puVar5[2];
        fVar9 = (float10)FUN_00822d60(*(undefined4 *)(local_26c + 0x30),
                                      *(undefined4 *)(local_26c + 0x34),
                                      *(undefined4 *)(local_26c + 0x38));
        puVar5 = (undefined4 *)FUN_00439d00(local_390,local_238,local_234,local_230,(float)fVar9);
        local_220 = *puVar5;
        local_21c = puVar5[1];
        local_218 = puVar5[2];
        local_280 = *(int *)(*(int *)(local_26c + 0xc) + 0x3c);
        local_80 = local_220;
        local_7c = local_21c;
        local_78 = local_218;
        if (local_280 != 0) {
          puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_254 + 0x34) + 0x18) + 0xc))();
          fVar9 = (float10)FUN_004620b0(local_220,local_21c,local_218,*puVar5,puVar5[1],puVar5[2]);
          local_2c4 = (float)fVar9;
          if (local_2c4 < *(float *)(local_280 + 0x50) * *(float *)(local_280 + 0x50))
          goto LAB_00476f79;
        }
        puVar5 = (undefined4 *)
                 FUN_004624b0(*(undefined4 *)(local_26c + 0x30),*(undefined4 *)(local_26c + 0x34),
                              *(undefined4 *)(local_26c + 0x38));
        puVar5 = (undefined4 *)FUN_004401a0(local_348,*puVar5,puVar5[1],puVar5[2]);
        local_170 = *puVar5;
        local_16c = puVar5[1];
        local_168 = puVar5[2];
        local_8c = local_170;
        local_88 = local_16c;
        local_84 = local_168;
        puVar5 = (undefined4 *)(**(code **)(local_260[6] + 0xc))(local_220,local_21c,local_218);
        puVar5 = (undefined4 *)FUN_004401a0(local_36c,*puVar5,puVar5[1],puVar5[2]);
        local_164 = *puVar5;
        local_160 = puVar5[1];
        local_15c = puVar5[2];
        local_68 = local_164;
        local_64 = local_160;
        local_60 = local_15c;
        fVar9 = (float10)FUN_004428b0(&local_170,&local_164);
        local_298 = (float)fVar9;
        if (0.0 < local_298) {
          (**(code **)(*local_258 + 8))();
        }
      }
    }
    else if (local_270 == 0) {
      if ((local_259 == '\0') || (local_265 == '\0')) {
        fVar9 = (float10)FUN_00453f80();
        local_2f8 = (float)fVar9;
        if (local_2f8 < 0.001) {
          fVar9 = (float10)FUN_00453f80();
          local_2b4 = (float)fVar9;
          if (local_2b4 < 0.001) {
            (**(code **)(*local_258 + 8))();
          }
        }
      }
      else {
        puVar5 = (undefined4 *)(**(code **)(local_260[6] + 0xc))();
        puVar5 = (undefined4 *)
                 (**(code **)(*(int *)(*(int *)(local_254 + 0x34) + 0x18) + 0xc))
                           (*puVar5,puVar5[1],puVar5[2]);
        fVar9 = (float10)FUN_004620b0(*puVar5,puVar5[1],puVar5[2]);
        local_29c = (float)fVar9;
        fVar9 = (float10)FUN_00820570((double)(local_29c + 0.0001));
        local_2a4 = (float)fVar9;
        fVar9 = (float10)FUN_00462470();
        local_2e8 = (float)fVar9;
        local_28c = local_2e8 * 0.5 * local_2a4;
        fVar9 = (float10)FUN_00453f80();
        local_2d4 = (float)fVar9;
        if (local_2d4 < local_28c) {
          fVar9 = (float10)FUN_00453f80();
          local_2ac = (float)fVar9;
          if (local_2ac < local_28c) {
            (**(code **)(*local_258 + 8))();
          }
        }
      }
    }
  }
  else {
    puVar5 = (undefined4 *)(**(code **)(local_260[6] + 0xc))();
    puVar5 = (undefined4 *)
             (**(code **)(*(int *)(*(int *)(local_254 + 0x34) + 0x18) + 0xc))
                       (*puVar5,puVar5[1],puVar5[2]);
    fVar9 = (float10)FUN_004620b0(*puVar5,puVar5[1],puVar5[2]);
    local_2dc = (float)fVar9;
    local_284 = *(float *)(local_258[3] + 0xd0);
    if (local_2dc < local_284 * local_284) {
      (**(code **)(*local_258 + 8))();
    }
  }
LAB_00476f79:
  FUN_0083e885();
  return;
}

