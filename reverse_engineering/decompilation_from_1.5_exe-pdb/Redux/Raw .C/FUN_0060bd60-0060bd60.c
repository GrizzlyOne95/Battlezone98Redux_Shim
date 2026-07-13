
void __thiscall FUN_0060bd60(int param_1,float param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_448 [36];
  undefined1 local_424 [12];
  undefined1 local_418 [24];
  undefined1 local_400 [24];
  undefined1 local_3e8 [12];
  undefined1 local_3dc [12];
  undefined1 local_3d0 [24];
  undefined1 local_3b8 [24];
  undefined1 local_3a0 [12];
  undefined1 local_394 [12];
  undefined1 local_388 [24];
  float local_370;
  float local_36c;
  float local_368;
  float local_364;
  float local_360;
  float local_35c;
  float local_358;
  float local_354;
  float local_350;
  float local_34c;
  float local_348;
  float local_344;
  float local_340;
  float local_33c;
  float local_338;
  float local_334;
  float local_330;
  float local_32c;
  float local_328;
  int *local_324;
  float local_320;
  float local_31c;
  float local_318;
  float local_314;
  float local_310;
  float local_30c;
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
  uint local_2d0;
  float local_2cc;
  undefined4 local_2c8;
  float local_2c4;
  uint local_2c0;
  float local_2bc;
  uint local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  uint local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  float local_298;
  float local_294;
  float local_290;
  undefined4 local_28c;
  float local_288;
  float local_284;
  int local_280;
  float local_27c;
  float local_278;
  float local_274;
  int local_270;
  float local_26c;
  float local_268;
  undefined1 local_262;
  char local_261;
  float local_260;
  float local_25c;
  float local_258;
  undefined1 local_252;
  char local_251;
  int local_250;
  undefined4 *local_24c;
  float *local_248;
  int local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  float local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  float local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4 [20];
  undefined4 local_184;
  undefined4 local_164;
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
  undefined4 local_bc;
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
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
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
  local_270 = *(int *)(param_1 + 0xf8);
  local_24c = (undefined4 *)(*(int *)(param_1 + 0xf4) + 0x20);
  if (param_2 == 0.0) {
    local_2bc = 1e+30;
  }
  else {
    local_2bc = 1.0 / param_2;
  }
  local_294 = local_2bc;
  local_244 = param_1;
  puVar2 = (undefined4 *)FUN_00447f60();
  local_38 = *puVar2;
  local_34 = puVar2[1];
  local_30 = puVar2[2];
  local_2c = puVar2[3];
  local_28 = puVar2[4];
  local_24 = puVar2[5];
  FUN_00444f70(*(undefined4 *)(local_244 + 0xf0),local_38,local_34);
  local_28c = *(undefined4 *)(*(int *)(local_244 + 0x230) + 0xc4);
  local_2dc = *(float *)(*(int *)(local_244 + 0x230) + 200);
  local_262 = *(int *)(*(int *)(local_244 + 0x230) + 0xd4) != 0;
  local_2a8 = (uint)(byte)local_262;
  if ((bool)local_262) {
    local_2b0 = 2.0;
  }
  else {
    local_2b0 = *(float *)(*(int *)(local_244 + 0x230) + 0xd0);
  }
  local_25c = local_2b0;
  local_26c = *(float *)(*(int *)(local_244 + 0x230) + 0xcc);
  local_261 = *(int *)(*(int *)(local_244 + 0x230) + 0xd8) != 0;
  local_2b8 = (uint)(byte)local_261;
  local_251 = *(int *)(local_244 + 0xfc) == 0;
  local_2c0 = (uint)(byte)local_251;
  local_27c = local_2b0 * local_2b0 + local_26c * local_26c;
  if (1.0 < local_27c) {
    local_27c = 1.0;
  }
  puVar2 = (undefined4 *)FUN_00439d80();
  local_234 = *puVar2;
  local_230 = (float)puVar2[1];
  local_22c = puVar2[2];
  local_50 = local_234;
  local_4c = local_230;
  local_48 = local_22c;
  puVar2 = (undefined4 *)FUN_004795e0();
  local_240 = *puVar2;
  local_23c = puVar2[1];
  local_238 = puVar2[2];
  local_c8 = local_240;
  local_c4 = local_23c;
  local_c0 = local_238;
  puVar2 = (undefined4 *)FUN_004560b0();
  local_21c = *puVar2;
  local_218 = (float)puVar2[1];
  local_214 = puVar2[2];
  local_68 = local_21c;
  local_64 = local_218;
  local_60 = local_214;
  fVar5 = (float10)FUN_004428b0();
  local_288 = (float)fVar5;
  fVar5 = (float10)FUN_004428b0();
  local_284 = (float)fVar5;
  if ((-1 < *(int *)(local_244 + 0x2ac)) &&
     ((((*(uint *)(*(int *)(local_244 + 0xf4) + 0x14) & 0x200) != 0 ||
       (iVar3 = FUN_0062a540(), iVar3 != 0)) || (*local_324 != 1)))) {
    FUN_0062a5d0();
    *(undefined4 *)(local_244 + 0x2ac) = 0xffffffff;
  }
  local_250 = *(int *)(local_244 + 0x2a8);
  local_260 = -1e+30;
  local_2c8 = *(undefined4 *)(local_244 + 0x228);
  switch(local_2c8) {
  case 0:
    if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0x80) == 0) {
      local_260 = 0.0;
    }
    else if (local_251 == '\0') {
      if (*(float *)(local_244 + 0x11c) <= 0.1) {
        local_250 = 2;
      }
      else {
        fVar5 = (float10)FUN_00453f80();
        local_318 = (float)fVar5;
        local_310 = local_318;
        fVar5 = (float10)FUN_00453f80();
        local_320 = (float)fVar5;
        if (local_318 <= local_320) {
          if (local_284 <= 0.0) {
            local_250 = 6;
            local_260 = -local_284 * *(float *)(*(int *)(local_244 + 0xf8) + 0x3f4);
          }
          else {
            local_250 = 7;
            local_260 = *(float *)(*(int *)(local_244 + 0xf8) + 0x3f4) * local_284;
          }
        }
        else if (local_288 <= 0.0) {
          local_250 = 5;
          local_260 = -local_288 * *(float *)(*(int *)(local_244 + 0xf8) + 0x3f4);
        }
        else {
          local_250 = 4;
          local_260 = *(float *)(*(int *)(local_244 + 0xf8) + 0x3f4) * local_288;
        }
      }
    }
    else {
      local_250 = 0;
      *(undefined4 *)(local_244 + 0x228) = 1;
    }
    break;
  case 1:
    if (*(int *)(local_244 + 0x2ac) == -1) {
      local_250 = 3;
      *(undefined4 *)(local_244 + 0x228) = 2;
    }
    else {
      local_250 = 0;
    }
    break;
  case 2:
    if (local_251 == '\0') {
      local_250 = 1;
      *(undefined4 *)(local_244 + 0x228) = 3;
    }
    else {
      local_250 = 3;
    }
    break;
  case 3:
    if (*(int *)(local_244 + 0x2ac) == -1) {
      local_250 = 2;
      *(undefined4 *)(local_244 + 0x228) = 0;
    }
    else {
      local_250 = 1;
    }
  }
  if (*(int *)(local_244 + 0x2a8) != local_250) {
    if (-1 < *(int *)(local_244 + 0x2ac)) {
      FUN_0062a5d0();
    }
    *(int *)(local_244 + 0x2a8) = local_250;
    FUN_0062a270();
  }
  if ((-1 < *(int *)(local_244 + 0x2ac)) && (0.0 <= local_260)) {
    FUN_0062a5a0();
  }
  if ((-1 < *(int *)(local_244 + 0x2ac)) && (FUN_0062a540(), *(int *)(local_280 + 0x1c) < 0)) {
    local_252 = (float)(*(int *)(local_280 + 0x10) + *(int *)(local_280 + 0x14)) * 0.5 <
                *(float *)(local_280 + 0xc);
    local_2d0 = (uint)(byte)local_252;
    if (*(char *)(local_244 + 0x2b0) != local_252) {
      *(undefined1 *)(local_244 + 0x2b0) = local_252;
      FUN_0043a990();
      local_184 = 0x4000;
      FUN_0043a9e0();
      if ((*(uint *)(*(int *)(local_244 + 0xf4) + 0x14) & 0x10) == 0) {
        local_164 = 0x2d;
      }
      else {
        local_164 = 0x41;
      }
      FUN_0043aa30();
    }
  }
  if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0x80) == 0) {
    local_248 = (float *)(local_270 + 0x390);
  }
  else if (*(int *)(local_244 + 0x228) == 0) {
    local_248 = (float *)(local_270 + 0x35c);
  }
  else {
    local_248 = (float *)(local_270 + 0x328);
  }
  fVar5 = (float10)FUN_004e9610();
  local_258 = (float)fVar5;
  local_2ac = local_258 * local_248[1];
  local_300 = local_258 * *local_248;
  local_2f4 = local_258 * local_248[5];
  local_2a4 = local_258 * local_248[6];
  local_2c4 = local_258 * local_248[7];
  local_304 = local_258 * local_248[8];
  local_268 = local_258 * local_248[9];
  local_290 = local_258 * local_248[10];
  local_2a0 = local_258 * local_248[0xb];
  local_2f8 = local_258 * local_248[0xc];
  *(undefined4 *)(local_244 + 0x144) = 0;
  *(undefined4 *)(local_244 + 0x148) = 0xc11ccccd;
  *(undefined4 *)(local_244 + 0x14c) = 0;
  if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0x80) == 0) {
    if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 4) == 0) {
      if (*(int *)(*(int *)(local_244 + 0x230) + 0xdc) != 0) {
        *(undefined4 *)(*(int *)(local_244 + 0x230) + 0xdc) = 0;
        *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
             *(uint *)(*(int *)(local_244 + 0x230) + 0x114) | 8;
      }
      if (((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 8) != 0) &&
         (*(float *)(local_244 + 0x130) <= -0.0 && *(float *)(local_244 + 0x130) != -0.0)) {
        *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
             *(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0xfffffff7;
        *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
             *(uint *)(*(int *)(local_244 + 0x230) + 0x114) | 4;
      }
      *(undefined4 *)(local_244 + 0x150) = 0;
      *(undefined4 *)(local_244 + 0x158) = 0;
      local_2d4 = (local_290 - local_268) * local_27c + local_268;
      if (0.0 < local_2d4) {
        fVar5 = (float10)FUN_00447ed0();
        local_354 = (float)fVar5;
        *(float *)(local_244 + 0x154) = local_354 * local_2a0;
      }
    }
    else {
      local_308 = -local_300;
      *(float *)(local_244 + 0x150) = local_308 * *(float *)(local_244 + 0x138);
      *(float *)(local_244 + 0x158) = local_308 * *(float *)(local_244 + 0x140);
      *(float *)(local_244 + 0x150) = *(float *)(local_244 + 0x150) - local_2ac * local_218;
      *(float *)(local_244 + 0x158) = local_2ac * local_230 + *(float *)(local_244 + 0x158);
      local_358 = local_248[2] * local_2ac;
      local_344 = local_248[3] * local_2ac;
      *(float *)(local_244 + 0x150) =
           (local_358 * local_2dc - local_344 * local_25c) + *(float *)(local_244 + 0x150);
      local_31c = local_248[4] * local_2ac;
      *(float *)(local_244 + 0x158) = local_31c * local_26c + *(float *)(local_244 + 0x158);
      local_2b4 = (local_290 - local_268) * local_27c + local_268;
      local_278 = local_2ac;
      if (0.0 < local_2b4) {
        fVar5 = (float10)FUN_00447ed0();
        local_35c = (float)fVar5;
        *(float *)(local_244 + 0x154) = local_35c * local_2a0;
      }
      if (local_25c <= 0.0) {
        local_2e4 = local_2a4;
      }
      else {
        local_2e4 = local_2f4;
      }
      local_30c = local_2e4;
      puVar2 = (undefined4 *)FUN_00459570(local_448,local_25c * local_2e4);
      local_210 = *puVar2;
      local_20c = puVar2[1];
      local_208 = puVar2[2];
      local_44 = local_210;
      local_40 = local_20c;
      local_3c = local_208;
      puVar2 = (undefined4 *)FUN_004401a0();
      local_210 = *puVar2;
      local_58 = puVar2[1];
      local_208 = puVar2[2];
      local_20c = 0;
      local_5c = local_210;
      local_54 = local_208;
      puVar2 = (undefined4 *)FUN_004462d0();
      local_204 = *puVar2;
      local_200 = puVar2[1];
      local_1fc = puVar2[2];
      local_29c = local_304;
      local_74 = local_204;
      local_70 = local_200;
      local_6c = local_1fc;
      fVar5 = (float10)FUN_004428b0();
      local_2cc = (float)fVar5;
      if (local_29c * local_29c < local_2cc) {
        fVar5 = (float10)FUN_00820570();
        local_34c = (float)fVar5;
        local_32c = local_34c;
        puVar2 = (undefined4 *)FUN_004462d0();
        local_204 = *puVar2;
        local_200 = puVar2[1];
        local_1fc = puVar2[2];
        local_8c = local_204;
        local_88 = local_200;
        local_84 = local_1fc;
      }
      puVar2 = (undefined4 *)FUN_00440130();
      local_a4 = *puVar2;
      local_a0 = puVar2[1];
      local_9c = puVar2[2];
      *(undefined4 *)(local_244 + 0x144) = local_a4;
      *(undefined4 *)(local_244 + 0x148) = local_a0;
      *(undefined4 *)(local_244 + 0x14c) = local_9c;
      local_36c = *(float *)(local_244 + 0x11c) * -0.1;
      fVar5 = (float10)FUN_004428b0();
      local_334 = (float)fVar5;
      local_2ec = local_36c * local_334;
      if (0.0 < local_2ec) {
        puVar2 = (undefined4 *)FUN_00439d00(local_388);
        local_bc = *puVar2;
        local_b8 = puVar2[1];
        local_b4 = puVar2[2];
        *(undefined4 *)(local_244 + 0x144) = local_bc;
        *(undefined4 *)(local_244 + 0x148) = local_b8;
        *(undefined4 *)(local_244 + 0x14c) = local_b4;
      }
    }
  }
  else {
    local_2d8 = -local_300;
    *(float *)(local_244 + 0x150) = local_2d8 * *(float *)(local_244 + 0x138);
    *(float *)(local_244 + 0x158) = local_2d8 * *(float *)(local_244 + 0x140);
    puVar2 = (undefined4 *)FUN_00440000();
    local_228 = *puVar2;
    local_224 = puVar2[1];
    local_220 = puVar2[2];
    local_134 = local_228;
    local_130 = local_224;
    local_12c = local_220;
    puVar2 = (undefined4 *)FUN_004621a0();
    local_228 = *puVar2;
    local_224 = puVar2[1];
    local_220 = puVar2[2];
    local_274 = local_2ac;
    local_80 = local_228;
    local_7c = local_224;
    local_78 = local_220;
    fVar5 = (float10)FUN_004428b0();
    local_328 = (float)fVar5;
    *(float *)(local_244 + 0x150) = *(float *)(local_244 + 0x150) - local_328 * local_274;
    fVar5 = (float10)FUN_004428b0();
    local_330 = (float)fVar5;
    *(float *)(local_244 + 0x158) = local_330 * local_274 + *(float *)(local_244 + 0x158);
    local_338 = local_248[2] * local_274;
    local_340 = local_248[3] * local_274;
    *(float *)(local_244 + 0x150) =
         (local_338 * local_2dc - local_340 * local_25c) + *(float *)(local_244 + 0x150);
    local_348 = local_248[4] * local_274;
    *(float *)(local_244 + 0x158) = local_348 * local_26c + *(float *)(local_244 + 0x158);
    local_2e0 = (local_290 - local_268) * local_27c + local_268;
    if (0.0 < local_2e0) {
      fVar5 = (float10)FUN_00447ed0();
      local_350 = (float)fVar5;
      *(float *)(local_244 + 0x154) = local_350 * local_2a0;
    }
    if (local_25c <= 0.0) {
      local_2e8 = local_2a4;
    }
    else {
      local_2e8 = local_2f4;
    }
    local_360 = local_2e8;
    puVar2 = (undefined4 *)FUN_00459570(local_394,local_25c * local_2e8);
    local_1e0 = *puVar2;
    local_1dc = puVar2[1];
    local_1d8 = puVar2[2];
    local_ec = local_1e0;
    local_e8 = local_1dc;
    local_e4 = local_1d8;
    fVar5 = (float10)FUN_004428b0();
    local_368 = (float)fVar5;
    puVar2 = (undefined4 *)FUN_00439d00(local_424);
    local_1e0 = *puVar2;
    local_1dc = puVar2[1];
    local_1d8 = puVar2[2];
    local_98 = local_1e0;
    local_94 = local_1dc;
    local_90 = local_1d8;
    puVar2 = (undefined4 *)FUN_004401a0();
    local_1e0 = *puVar2;
    local_1dc = puVar2[1];
    local_1d8 = puVar2[2];
    local_11c = local_1e0;
    local_118 = local_1dc;
    local_114 = local_1d8;
    puVar2 = (undefined4 *)FUN_004462d0();
    local_1f8 = *puVar2;
    local_1f4 = puVar2[1];
    local_1f0 = puVar2[2];
    local_298 = local_304;
    local_b0 = local_1f8;
    local_ac = local_1f4;
    local_a8 = local_1f0;
    fVar5 = (float10)FUN_004428b0();
    local_2f0 = (float)fVar5;
    if (local_298 * local_298 < local_2f0) {
      fVar5 = (float10)FUN_00820570();
      local_370 = (float)fVar5;
      local_314 = local_370;
      puVar2 = (undefined4 *)FUN_004462d0();
      local_1f8 = *puVar2;
      local_1f4 = puVar2[1];
      local_1f0 = puVar2[2];
      local_104 = local_1f8;
      local_100 = local_1f4;
      local_fc = local_1f0;
    }
    puVar2 = (undefined4 *)FUN_00440130();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    *(undefined4 *)(local_244 + 0x144) = local_14;
    *(undefined4 *)(local_244 + 0x148) = local_10;
    *(undefined4 *)(local_244 + 0x14c) = local_c;
    if ((local_261 != '\0') && (0.0 < local_2f8)) {
      FUN_004376c0();
      puVar2 = (undefined4 *)FUN_00439d00(local_3dc);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      *(undefined4 *)(local_244 + 0x144) = local_20;
      *(undefined4 *)(local_244 + 0x148) = local_1c;
      *(undefined4 *)(local_244 + 0x14c) = local_18;
    }
  }
  puVar2 = (undefined4 *)FUN_00439d00(local_3a0);
  local_e0 = *puVar2;
  local_dc = puVar2[1];
  local_d8 = puVar2[2];
  *(undefined4 *)(local_244 + 0x138) = local_e0;
  *(undefined4 *)(local_244 + 0x13c) = local_dc;
  *(undefined4 *)(local_244 + 0x140) = local_d8;
  puVar2 = (undefined4 *)FUN_00444d50();
  puVar4 = local_1d4;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_1d4;
  puVar4 = local_24c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)FUN_00439d00(local_3b8);
  local_f8 = *puVar2;
  local_f4 = puVar2[1];
  local_f0 = puVar2[2];
  *(undefined4 *)(local_244 + 0x138) = local_f8;
  *(undefined4 *)(local_244 + 0x13c) = local_f4;
  *(undefined4 *)(local_244 + 0x140) = local_f0;
  if (*(float *)(local_244 + 0x138) <= -12.0 && *(float *)(local_244 + 0x138) != -12.0) {
    *(undefined4 *)(local_244 + 0x138) = 0xc1400000;
  }
  if (12.0 < *(float *)(local_244 + 0x138)) {
    *(undefined4 *)(local_244 + 0x138) = 0x41400000;
  }
  if (*(float *)(local_244 + 0x13c) <= -12.0 && *(float *)(local_244 + 0x13c) != -12.0) {
    *(undefined4 *)(local_244 + 0x13c) = 0xc1400000;
  }
  if (12.0 < *(float *)(local_244 + 0x13c)) {
    *(undefined4 *)(local_244 + 0x13c) = 0x41400000;
  }
  if (*(float *)(local_244 + 0x140) <= -12.0 && *(float *)(local_244 + 0x140) != -12.0) {
    *(undefined4 *)(local_244 + 0x140) = 0xc1400000;
  }
  if (12.0 < *(float *)(local_244 + 0x140)) {
    *(undefined4 *)(local_244 + 0x140) = 0x41400000;
  }
  puVar2 = (undefined4 *)FUN_00439d00(local_3d0);
  local_110 = *puVar2;
  local_10c = puVar2[1];
  local_108 = puVar2[2];
  *(undefined4 *)(local_244 + 300) = local_110;
  *(undefined4 *)(local_244 + 0x130) = local_10c;
  *(undefined4 *)(local_244 + 0x134) = local_108;
  *(double *)(local_24c + 10) =
       (double)(*(float *)(local_244 + 300) * param_2) + *(double *)(local_24c + 10);
  *(double *)(local_24c + 0xc) =
       (double)(*(float *)(local_244 + 0x130) * param_2) + *(double *)(local_24c + 0xc);
  *(double *)(local_24c + 0xe) =
       (double)(*(float *)(local_244 + 0x134) * param_2) + *(double *)(local_24c + 0xe);
  puVar2 = (undefined4 *)FUN_00439d00(local_3e8);
  local_128 = *puVar2;
  local_124 = puVar2[1];
  local_120 = puVar2[2];
  *(undefined4 *)(local_244 + 300) = local_128;
  *(undefined4 *)(local_244 + 0x130) = local_124;
  *(undefined4 *)(local_244 + 0x134) = local_120;
  if ((double)local_2fc < *(double *)(local_24c + 0xc)) {
    *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
         *(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0xffffff7f;
  }
  else {
    puVar2 = (undefined4 *)FUN_00439d00(local_400);
    local_14c = *puVar2;
    local_148 = puVar2[1];
    local_144 = puVar2[2];
    local_140 = local_14c;
    local_13c = local_148;
    local_138 = local_144;
    fVar5 = (float10)FUN_004428b0();
    local_33c = (float)fVar5;
    if (local_33c < 0.0) {
      FUN_008245f0();
    }
    if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0x80) == 0) {
      if ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 4) == 0) {
        *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
             *(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0xfffffff7;
      }
      else {
        *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
             *(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0xfffffff3;
      }
      *(uint *)(*(int *)(local_244 + 0x230) + 0x114) =
           *(uint *)(*(int *)(local_244 + 0x230) + 0x114) | 0x80;
    }
    fVar5 = (float10)FUN_004428b0();
    local_364 = (float)fVar5;
    puVar2 = (undefined4 *)FUN_00439d00(local_418);
    local_d4 = *puVar2;
    local_d0 = puVar2[1];
    local_cc = puVar2[2];
    *(undefined4 *)(local_244 + 300) = local_d4;
    *(undefined4 *)(local_244 + 0x130) = local_d0;
    *(undefined4 *)(local_244 + 0x134) = local_cc;
    *(double *)(local_24c + 0xc) = (double)local_2fc;
  }
  fVar5 = (float10)FUN_0045c420();
  *(float *)(local_244 + 0x11c) = (float)fVar5;
  *(float *)(local_244 + 0x280) = *(float *)(*(int *)(local_244 + 0x230) + 200) * 0.5;
  if ((((*(uint *)(*(int *)(local_244 + 0xf4) + 0x14) & 0x10) != 0) &&
      (iVar3 = FUN_004e96a0(), iVar3 != 0)) ||
     ((cVar1 = FUN_004b9830(), cVar1 != '\0' &&
      ((*(uint *)(*(int *)(local_244 + 0x230) + 0x114) & 0x1000) != 0)))) {
    *(float *)(local_244 + 0x280) =
         *(float *)(local_244 + 0x280) - *(float *)(*(int *)(local_244 + 0xf4) + 0x3c);
  }
  FUN_004ab380();
  FUN_0083e885();
  return;
}

