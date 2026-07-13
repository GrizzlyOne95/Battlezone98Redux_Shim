
void __fastcall FUN_005b70e0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_330 [12];
  undefined1 local_324 [36];
  undefined1 local_300 [48];
  undefined1 local_2d0 [36];
  undefined1 local_2ac [60];
  undefined1 local_270 [28];
  float local_254;
  float local_250;
  float local_24c;
  float local_248;
  undefined8 local_244;
  float local_23c;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  undefined4 local_220;
  uint local_21c;
  float local_218;
  undefined4 local_214;
  uint local_210;
  float local_20c;
  int local_208;
  int local_204;
  int local_200;
  int local_1fc;
  int *local_1f8;
  float *local_1f4;
  int local_1f0;
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
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  float local_fc;
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
  local_1e0 = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x2c) + 0x230) + 0xc4);
  local_1dc = param_1;
  local_1e8 = FUN_0045c4d0();
  puVar2 = (undefined4 *)FUN_00447f60();
  local_dc = *puVar2;
  local_d8 = puVar2[1];
  local_d4 = puVar2[2];
  local_d0 = puVar2[3];
  local_cc = puVar2[4];
  local_c8 = puVar2[5];
  local_a0 = local_dc;
  uStack_9c = local_d8;
  local_98 = local_d4;
  uStack_94 = local_d0;
  local_90 = local_cc;
  uStack_8c = local_c8;
  uVar3 = (**(code **)(*(int *)(*(int *)(local_1dc + 0x2c) + 0x18) + 0x2c))
                    (local_dc,local_d8,local_d4,local_d0,local_cc,local_c8);
  FUN_00444f70(uVar3);
  puVar2 = (undefined4 *)FUN_004560b0();
  local_13c = *puVar2;
  local_138 = puVar2[1];
  local_134 = puVar2[2];
  local_124 = local_13c;
  local_120 = local_138;
  local_11c = local_134;
  fVar5 = (float10)FUN_004428b0();
  local_254 = (float)fVar5;
  fVar5 = (float10)FUN_00447ed0();
  local_1e0[1] = (float)fVar5;
  local_1e1 = 0.7 < local_fc;
  local_210 = (uint)(byte)local_1e1;
  local_1f4 = (float *)(**(code **)(*(int *)(*(int *)(local_1dc + 0x2c) + 0x18) + 0xc))();
  local_214 = *(undefined4 *)(local_1dc + 0x28);
  local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
  switch(local_214) {
  case 0:
    local_1e0[3] = 0xbdcccccd;
    *local_1e0 = 0;
    local_1e0[4] = 0;
    cVar1 = FUN_00466d40();
    if (cVar1 == '\0') {
      fVar5 = (float10)FUN_00822d80();
      local_228 = (float)fVar5;
      *(float *)(local_1dc + 0x18) = local_228 + 2.0;
      *(undefined4 *)(local_1dc + 0x28) = 10;
      local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
    }
    else {
      fVar5 = (float10)FUN_00822d80();
      local_224 = (float)fVar5;
      *(float *)(local_1dc + 0x18) = local_224 + 2.0;
      local_1ec = 50.0;
      local_208 = 8;
      FUN_005b2950((double)(*local_1f4 - 50.0),(double)(local_1f4[2] - 50.0),
                   (double)(*local_1f4 + 50.0));
      puVar2 = (undefined4 *)FUN_004560b0();
      local_f4 = *puVar2;
      local_f0 = puVar2[1];
      local_ec = puVar2[2];
      local_68[0] = local_f4;
      local_68[1] = local_f0;
      local_68[2] = local_ec;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_184 = *puVar2;
      local_180 = puVar2[1];
      local_17c = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_190 = *puVar2;
      local_18c = puVar2[1];
      local_188 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_330,0x3f3504f7,local_190,local_18c,local_188,0x3f3504f7);
      local_118 = *puVar2;
      local_114 = puVar2[1];
      local_110 = puVar2[2];
      local_68[3] = local_118;
      local_58 = local_114;
      local_54 = local_110;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_10c = *puVar2;
      local_108 = puVar2[1];
      local_104 = puVar2[2];
      local_50 = local_10c;
      local_4c = local_108;
      local_48 = local_104;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_1cc = *puVar2;
      local_1c8 = puVar2[1];
      local_1c4 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_1b4 = *puVar2;
      local_1b0 = puVar2[1];
      local_1ac = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_324,0xbf3504f7,local_1b4,local_1b0,local_1ac,0x3f3504f7);
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
      puVar2 = (undefined4 *)FUN_004462d0(local_300,0xbf800000);
      local_b8 = *puVar2;
      local_b4 = puVar2[1];
      local_b0 = puVar2[2];
      local_38 = local_b8;
      local_34 = local_b4;
      local_30 = local_b0;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_16c = *puVar2;
      local_168 = puVar2[1];
      local_164 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_1a8 = *puVar2;
      local_1a4 = puVar2[1];
      local_1a0 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_2d0,0xbf3504f7,local_1a8,local_1a4,local_1a0,0xbf3504f7);
      local_130 = *puVar2;
      local_12c = puVar2[1];
      local_128 = puVar2[2];
      local_2c = local_130;
      local_28 = local_12c;
      local_24 = local_128;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_1c0 = *puVar2;
      local_1bc = puVar2[1];
      local_1b8 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004462d0(local_270,0xbf800000);
      local_c4 = *puVar2;
      local_c0 = puVar2[1];
      local_bc = puVar2[2];
      local_20 = local_c4;
      local_1c = local_c0;
      local_18 = local_bc;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_1d8 = *puVar2;
      local_1d4 = puVar2[1];
      local_1d0 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004560b0();
      local_19c = *puVar2;
      local_198 = puVar2[1];
      local_194 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00459570(local_2ac,0x3f3504f7,local_19c,local_198,local_194,0xbf3504f7);
      local_e8 = *puVar2;
      local_e4 = puVar2[1];
      local_e0 = puVar2[2];
      local_14 = local_e8;
      local_10 = local_e4;
      local_c = local_e0;
      for (local_1fc = 0; local_1fc < 8; local_1fc = local_1fc + 1) {
        local_218 = local_1ec;
        iVar4 = FUN_00784620(local_a0,uStack_9c,local_98,uStack_94,local_90,uStack_8c,
                             local_68[local_1fc * 3]);
        if ((iVar4 == 0) || (0.7 <= local_150)) {
          afStack_88[local_1fc] = local_1ec;
        }
        else {
          afStack_88[local_1fc] = local_218;
        }
      }
      iVar4 = (*(code *)**(undefined4 **)(*(int *)(local_1dc + 0x2c) + 0x18))();
      local_204 = iVar4 + 0x10c;
      local_148 = (float)(double)CONCAT44(uStack_9c,local_a0);
      local_144 = (float)((double)((*(float *)(iVar4 + 0x11c) + *(float *)(iVar4 + 0x110)) * 0.5) +
                         (double)CONCAT44(uStack_94,local_98));
      local_140 = (float)(double)CONCAT44(uStack_8c,local_90);
      local_23c = (*(float *)(iVar4 + 0x11c) - *(float *)(iVar4 + 0x110)) * 0.5;
      while (cVar1 = FUN_00462710(), cVar1 != '\0') {
        local_1f8 = (int *)FUN_004da060();
        if ((local_1f8 != (int *)0x0) && (local_1f8 != *(int **)(local_1dc + 0x2c))) {
          local_220 = (**(code **)(local_1f8[6] + 0x30))();
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
      local_1f0 = 0;
      while( true ) {
        if (7 < local_1f0) break;
        fVar5 = (float10)FUN_00466de0();
        local_20c = (float)fVar5;
        if ((local_20c < local_1ec) && (local_20c < afStack_88[local_1f0])) {
          local_208 = local_1f0;
          local_1ec = local_20c;
        }
        local_1f0 = local_1f0 + 1;
      }
      if ((local_208 == 8) || ((local_1e1 == '\0' && (10.0 < local_1ec)))) {
        *(undefined4 *)(local_1dc + 0x28) = 9;
        local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
      }
      else {
        *(int *)(local_1dc + 0x28) = local_208 + 1;
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
    local_22c = (float)fVar5;
    if (local_22c < *(float *)(local_1dc + 0x18) || local_22c == *(float *)(local_1dc + 0x18)) {
      cVar1 = FUN_00466d40();
      if (cVar1 == '\0') {
        *(undefined4 *)(local_1dc + 0x4c) = 0;
        local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
      }
      else {
        local_1e0[3] = (&PTR_s_NO_STATE_008e9030)[*(int *)(local_1dc + 0x28)];
        *local_1e0 = 0;
        local_21c = (uint)(0.0 < (float)(&PTR_s_NO_STATE_008e9030)[*(int *)(local_1dc + 0x28)]);
        local_1e0[4] = local_21c;
        local_1e0[2] = (&PTR_s_GOTO_GEYSER_008e8fec)[*(int *)(local_1dc + 0x28)];
        local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
      }
    }
    else {
      if (local_1e1 == '\0') {
        *(undefined4 *)(local_1dc + 0x28) = 9;
      }
      else {
        *(undefined4 *)(local_1dc + 0x28) = 0;
      }
      fVar5 = (float10)FUN_00822d80();
      local_250 = (float)fVar5;
      *(float *)(local_1dc + 0x18) = local_250 + 2.0;
      local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
    }
    break;
  case 9:
    fVar5 = (float10)FUN_00822d80();
    local_230 = (float)fVar5;
    if (local_230 < *(float *)(local_1dc + 0x18) || local_230 == *(float *)(local_1dc + 0x18)) {
      cVar1 = FUN_00466d40();
      if (cVar1 == '\0') {
        *(undefined4 *)(local_1dc + 0x4c) = 0;
        local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
      }
      else if (local_1e1 == '\0') {
        local_244 = FUN_0045c460();
        (**(code **)(**(int **)(local_1dc + 0x2c) + 0x8c))();
        fVar5 = (float10)FUN_00453f80();
        local_248 = (float)fVar5;
        if (0.25 <= local_248) {
          local_1e0[3] = 0;
        }
        else {
          local_1e0[3] = 0x3f800000;
        }
        local_1e0[4] = 0;
      }
      else {
        *(undefined4 *)(local_1dc + 0x28) = 6;
        fVar5 = (float10)FUN_00822d80();
        local_24c = (float)fVar5;
        *(float *)(local_1dc + 0x18) = local_24c + 2.0;
        local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
      }
    }
    else {
      *(undefined4 *)(local_1dc + 0x4c) = 0;
      local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
    }
    break;
  case 10:
    fVar5 = (float10)FUN_00822d80();
    local_234 = (float)fVar5;
    if (local_234 < *(float *)(local_1dc + 0x18) || local_234 == *(float *)(local_1dc + 0x18)) {
      local_1e0[3] = 0xbf800000;
      *local_1e0 = 0;
      local_1e0[4] = 0;
      local_1e0[2] = 0;
      local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
    }
    else {
      *(undefined4 *)(local_1dc + 0x4c) = 0;
      local_244 = CONCAT44(local_244._4_4_,(undefined4)local_244);
    }
  }
  FUN_0083e885();
  return;
}

