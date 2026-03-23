
void __fastcall FUN_006029b0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_334 [12];
  undefined1 local_328 [36];
  undefined1 local_304 [48];
  undefined1 local_2d4 [36];
  undefined1 local_2b0 [60];
  undefined1 local_274 [28];
  float local_258;
  undefined8 local_254;
  float local_24c;
  float local_248;
  float local_240;
  float local_23c;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  undefined4 local_21c;
  uint local_218;
  undefined4 local_214;
  uint local_210;
  int local_20c;
  float local_208;
  int local_204;
  int local_200;
  int local_1fc;
  int *local_1f8;
  int local_1f4;
  float *local_1f0;
  float local_1ec;
  undefined4 local_1e8;
  char local_1e1;
  undefined4 *local_1e0;
  int local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
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
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  float local_150;
  float local_148;
  float local_144;
  float local_140;
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
  float local_108;
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
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  float afStack_88 [8];
  undefined4 local_68 [4];
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
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1e0 = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_1dc = param_1;
  local_1e8 = FUN_0045c4d0();
  puVar2 = (undefined4 *)FUN_00447f60();
  local_124 = *puVar2;
  local_120 = puVar2[1];
  local_11c = puVar2[2];
  local_118 = puVar2[3];
  local_114 = puVar2[4];
  local_110 = puVar2[5];
  local_a0 = local_124;
  uStack_9c = local_120;
  local_98 = local_11c;
  uStack_94 = local_118;
  local_90 = local_114;
  uStack_8c = local_110;
  uVar3 = (**(code **)(*(int *)(*(int *)(local_1dc + 0x10) + 0x18) + 0x2c))
                    (local_124,local_120,local_11c,local_118,local_114,local_110);
  FUN_00444f70(uVar3);
  puVar2 = (undefined4 *)FUN_004560b0();
  local_13c = *puVar2;
  local_138 = puVar2[1];
  local_134 = puVar2[2];
  local_d0 = local_13c;
  local_cc = local_138;
  local_c8 = local_134;
  fVar5 = (float10)FUN_004428b0();
  local_238 = (float)fVar5;
  fVar5 = (float10)FUN_00447ed0();
  local_1e0[1] = (float)fVar5;
  local_1e1 = 0.7 < local_108;
  local_210 = (uint)(byte)local_1e1;
  local_1f0 = (float *)(**(code **)(*(int *)(*(int *)(local_1dc + 0x10) + 0x18) + 0xc))();
  local_21c = *(undefined4 *)(local_1dc + 0x94);
  local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
  switch(local_21c) {
  case 0:
    local_1e0[3] = 0xbdcccccd;
    *local_1e0 = 0;
    local_1e0[4] = 0;
    cVar1 = FUN_00466d40();
    if (cVar1 == '\0') {
      fVar5 = (float10)FUN_00822d80();
      local_258 = (float)fVar5;
      *(float *)(local_1dc + 0x84) = local_258 + 2.0;
      *(undefined4 *)(local_1dc + 0x94) = 10;
      local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    }
    else {
      fVar5 = (float10)FUN_00822d80();
      local_224 = (float)fVar5;
      *(float *)(local_1dc + 0x84) = local_224 + 2.0;
      local_1ec = 50.0;
      local_20c = 8;
      FUN_005b2950((double)(*local_1f0 - 50.0),(double)(local_1f0[2] - 50.0),
                   (double)(*local_1f0 + 50.0));
      puVar2 = (undefined4 *)FUN_004560b0();
      local_dc = *puVar2;
      local_d8 = puVar2[1];
      local_d4 = puVar2[2];
      local_68[0] = local_dc;
      local_68[1] = local_d8;
      local_68[2] = local_d4;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_1cc = *puVar2;
      local_1c8 = puVar2[1];
      local_1c4 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_1b4 = *puVar2;
      local_1b0 = puVar2[1];
      local_1ac = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_334,0x3f3504f7,local_1b4,local_1b0,local_1ac,0x3f3504f7);
      local_100 = *puVar2;
      local_fc = puVar2[1];
      local_f8 = puVar2[2];
      local_68[3] = local_100;
      local_58 = local_fc;
      local_54 = local_f8;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_130 = *puVar2;
      local_12c = puVar2[1];
      local_128 = puVar2[2];
      local_50 = local_130;
      local_4c = local_12c;
      local_48 = local_128;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_1d8 = *puVar2;
      local_1d4 = puVar2[1];
      local_1d0 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_1a8 = *puVar2;
      local_1a4 = puVar2[1];
      local_1a0 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_328,0xbf3504f7,local_1a8,local_1a4,local_1a0,0x3f3504f7);
      local_ac = *puVar2;
      local_a8 = puVar2[1];
      local_a4 = puVar2[2];
      local_44 = local_ac;
      local_40 = local_a8;
      local_3c = local_a4;
      puVar2 = (undefined4 *)FUN_004560b0();
      local_178 = *puVar2;
      local_174 = puVar2[1];
      local_170 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004462d0(local_304,0xbf800000);
      local_b8 = *puVar2;
      local_b4 = puVar2[1];
      local_b0 = puVar2[2];
      local_38 = local_b8;
      local_34 = local_b4;
      local_30 = local_b0;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_184 = *puVar2;
      local_180 = puVar2[1];
      local_17c = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_19c = *puVar2;
      local_198 = puVar2[1];
      local_194 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_2d4,0xbf3504f7,local_19c,local_198,local_194,0xbf3504f7);
      local_c4 = *puVar2;
      local_c0 = puVar2[1];
      local_bc = puVar2[2];
      local_2c = local_c4;
      local_28 = local_c0;
      local_24 = local_bc;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_16c = *puVar2;
      local_168 = puVar2[1];
      local_164 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004462d0(local_274,0xbf800000);
      local_e8 = *puVar2;
      local_e4 = puVar2[1];
      local_e0 = puVar2[2];
      local_20 = local_e8;
      local_1c = local_e4;
      local_18 = local_e0;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_190 = *puVar2;
      local_18c = puVar2[1];
      local_188 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_1c0 = *puVar2;
      local_1bc = puVar2[1];
      local_1b8 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_2b0,0x3f3504f7,local_1c0,local_1bc,local_1b8,0xbf3504f7);
      local_f4 = *puVar2;
      local_f0 = puVar2[1];
      local_ec = puVar2[2];
      local_14 = local_f4;
      local_10 = local_f0;
      local_c = local_ec;
      for (local_1fc = 0; local_1fc < 8; local_1fc = local_1fc + 1) {
        local_220 = local_1ec;
        iVar4 = FUN_00784620(local_a0,uStack_9c,local_98,uStack_94,local_90,uStack_8c,
                             local_68[local_1fc * 3]);
        if ((iVar4 == 0) || (0.7 <= local_150)) {
          afStack_88[local_1fc] = local_1ec;
        }
        else {
          fVar5 = (float10)FUN_00462470();
          local_22c = (float)fVar5;
          afStack_88[local_1fc] = local_220 - local_22c;
        }
      }
      iVar4 = (*(code *)**(undefined4 **)(*(int *)(local_1dc + 0x10) + 0x18))();
      local_204 = iVar4 + 0x10c;
      local_148 = (float)(double)CONCAT44(uStack_9c,local_a0);
      local_144 = (float)((double)((*(float *)(iVar4 + 0x11c) + *(float *)(iVar4 + 0x110)) * 0.5) +
                         (double)CONCAT44(uStack_94,local_98));
      local_140 = (float)(double)CONCAT44(uStack_8c,local_90);
      local_234 = (*(float *)(iVar4 + 0x11c) - *(float *)(iVar4 + 0x110)) * 0.5;
      while (cVar1 = FUN_00462710(), cVar1 != '\0') {
        local_1f8 = (int *)FUN_004da060();
        if ((local_1f8 != (int *)0x0) && (local_1f8 != *(int **)(local_1dc + 0x10))) {
          local_214 = (**(code **)(local_1f8[6] + 0x30))();
          iVar4 = FUN_0062e000();
          if ((iVar4 == 0) ||
             ((iVar4 = FUN_00417e20(), iVar4 != 0 &&
              (cVar1 = (**(code **)(*local_1f8 + 0x68))(), cVar1 != '\0')))) {
            for (local_200 = 0; local_200 < 8; local_200 = local_200 + 1) {
              FUN_00480a30();
            }
          }
        }
      }
      local_1f4 = 0;
      while( true ) {
        if (7 < local_1f4) break;
        fVar5 = (float10)FUN_00466de0();
        local_208 = (float)fVar5;
        if ((local_208 < local_1ec) && (local_208 < afStack_88[local_1f4])) {
          local_20c = local_1f4;
          local_1ec = local_208;
        }
        local_1f4 = local_1f4 + 1;
      }
      if ((local_20c == 8) || ((local_1e1 == '\0' && (10.0 < local_1ec)))) {
        *(undefined4 *)(local_1dc + 0x94) = 9;
        local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
      }
      else {
        *(int *)(local_1dc + 0x94) = local_20c + 1;
      }
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    fVar5 = (float10)FUN_00822d80();
    local_23c = (float)fVar5;
    if (local_23c < *(float *)(local_1dc + 0x84) || local_23c == *(float *)(local_1dc + 0x84)) {
      cVar1 = FUN_00466d40();
      if (cVar1 == '\0') {
        *(undefined4 *)(local_1dc + 0xc) = 1;
        local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
      }
      else {
        local_1e0[3] = (&PTR_s_USTATEX_008ea51c)[*(int *)(local_1dc + 0x94)];
        *local_1e0 = 0;
        local_218 = (uint)(0.0 < (float)(&PTR_s_USTATEX_008ea51c)[*(int *)(local_1dc + 0x94)]);
        local_1e0[4] = local_218;
        local_1e0[2] = (&PTR_s_default_backward__008ea4a0)[*(int *)(local_1dc + 0x94)];
        local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
      }
    }
    else {
      if (local_1e1 == '\0') {
        *(undefined4 *)(local_1dc + 0x94) = 9;
      }
      else {
        *(undefined4 *)(local_1dc + 0x94) = 0;
      }
      fVar5 = (float10)FUN_00822d80();
      local_24c = (float)fVar5;
      *(float *)(local_1dc + 0x84) = local_24c + 2.0;
      local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    }
    break;
  case 9:
    fVar5 = (float10)FUN_00822d80();
    local_228 = (float)fVar5;
    if (local_228 < *(float *)(local_1dc + 0x84) || local_228 == *(float *)(local_1dc + 0x84)) {
      cVar1 = FUN_00466d40();
      if (cVar1 == '\0') {
        *(undefined4 *)(local_1dc + 0xc) = 1;
        local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
      }
      else if (local_1e1 == '\0') {
        local_254 = FUN_0045c460();
        (**(code **)(**(int **)(local_1dc + 0x10) + 0x8c))();
        fVar5 = (float10)FUN_00453f80();
        local_240 = (float)fVar5;
        if (0.25 <= local_240) {
          local_1e0[3] = 0;
        }
        else {
          local_1e0[3] = 0x3f800000;
        }
        local_1e0[4] = 0;
      }
      else {
        *(undefined4 *)(local_1dc + 0x94) = 6;
        fVar5 = (float10)FUN_00822d80();
        local_230 = (float)fVar5;
        *(float *)(local_1dc + 0x84) = local_230 + 2.0;
        local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
      }
    }
    else {
      *(undefined4 *)(local_1dc + 0xc) = 1;
      local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    }
    break;
  case 10:
    fVar5 = (float10)FUN_00822d80();
    local_248 = (float)fVar5;
    if (local_248 < *(float *)(local_1dc + 0x84) || local_248 == *(float *)(local_1dc + 0x84)) {
      local_1e0[3] = 0xbf800000;
      *local_1e0 = 0;
      local_1e0[4] = 0;
      local_1e0[2] = 0;
      local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    }
    else {
      *(undefined4 *)(local_1dc + 0xc) = 1;
      local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    }
  }
  FUN_0083e885();
  return;
}

