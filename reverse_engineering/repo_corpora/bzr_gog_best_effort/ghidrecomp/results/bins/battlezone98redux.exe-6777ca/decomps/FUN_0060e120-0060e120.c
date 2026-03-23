
void FUN_0060e120(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float fVar7;
  undefined1 local_3a4 [76];
  undefined1 local_358 [12];
  undefined1 local_34c [24];
  undefined1 local_334 [12];
  undefined1 local_328 [12];
  undefined1 local_31c [12];
  undefined1 local_310 [12];
  undefined1 local_304 [12];
  undefined1 local_2f8 [12];
  undefined1 local_2ec [12];
  undefined1 local_2e0 [12];
  undefined1 local_2d4 [12];
  undefined1 local_2c8 [12];
  undefined1 local_2bc [12];
  undefined1 local_2b0 [12];
  undefined1 local_2a4 [12];
  undefined1 local_298 [12];
  undefined1 local_28c [12];
  undefined1 local_280 [12];
  undefined1 local_274 [12];
  undefined1 local_268 [36];
  float local_244;
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
  int local_20c;
  int local_208;
  undefined4 local_204 [6];
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
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
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  undefined4 local_15c [16];
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  float local_110;
  float local_10c;
  float local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_004b9830();
  if ((cVar1 == '\0') &&
     (((*(char *)(local_208 + 0x9c) == '\0' || (*(int *)(local_208 + 0xa0) == 0)) ||
      (iVar2 = (**(code **)(*(int *)(*(int *)(local_208 + 0xa0) + 0x18) + 0x30))(), param_1 != iVar2
      )))) {
    puVar3 = (undefined4 *)FUN_0062bf70();
    puVar5 = local_204;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = (undefined4 *)FUN_004401a0(local_280,local_1ec,local_1e8,local_1e4);
    local_11c = *puVar3;
    local_118 = puVar3[1];
    local_114 = puVar3[2];
    local_50 = local_11c;
    local_4c = local_118;
    local_48 = local_114;
    FUN_008245f0(*(undefined4 *)(local_208 + 0xf4),param_1);
    if (*(int *)(param_1 + 0x84) != 3) {
      fVar6 = (float10)FUN_00822d60();
      local_214 = (float)fVar6;
      local_20c = param_2;
      fVar6 = (float10)FUN_0045c420();
      *(float *)(local_208 + 0x11c) = (float)fVar6;
      if (*(float *)(local_208 + 0x11c) == 0.0) {
        local_224 = 1e+30;
      }
      else {
        local_224 = 1.0 / *(float *)(local_208 + 0x11c);
      }
      *(float *)(local_208 + 0x120) = local_224;
      local_174 = *(float *)(local_208 + 300);
      local_170 = *(float *)(local_208 + 0x130);
      local_16c = *(float *)(local_208 + 0x134);
      local_180 = *(undefined4 *)(local_20c + 0x6c);
      local_17c = *(undefined4 *)(local_20c + 0x70);
      local_178 = *(undefined4 *)(local_20c + 0x74);
      puVar3 = (undefined4 *)FUN_00440000(local_334);
      local_168 = (float)*puVar3;
      local_164 = (float)puVar3[1];
      local_160 = (float)puVar3[2];
      local_bc = local_168;
      local_b8 = local_164;
      local_b4 = local_160;
      puVar3 = (undefined4 *)
               FUN_004401a0(local_358,*(undefined4 *)(local_20c + 0x54),
                            *(undefined4 *)(local_20c + 0x58),*(undefined4 *)(local_20c + 0x5c));
      local_74 = *puVar3;
      local_70 = puVar3[1];
      local_6c = puVar3[2];
      local_14 = local_74;
      local_10 = local_70;
      local_c = local_6c;
      if (*(float *)(local_208 + 0x11c) <= 0.0001) {
        local_210 = 1.0;
      }
      else {
        fVar6 = (float10)FUN_004428b0();
        local_23c = (float)fVar6;
        fVar7 = local_23c * *(float *)(local_208 + 0x120);
        local_210 = 1.0 - fVar7 * 0.75 * fVar7;
      }
      iVar2 = FUN_0062e000();
      if ((iVar2 == 0) ||
         (*(float *)(local_20c + 8) <= 0.0001 && *(float *)(local_20c + 8) != 0.0001)) {
        fVar6 = (float10)FUN_004428b0(&local_180,&local_174);
        local_22c = (float)fVar6;
        pfVar4 = (float *)FUN_00439d00(local_268,local_174,local_170,local_16c,local_22c * -2.0);
        local_174 = *pfVar4;
        local_170 = pfVar4[1];
        local_16c = pfVar4[2];
        if (0.0001 < *(float *)(local_208 + 0x11c)) {
          local_210 = (1.0 - local_170 * 0.9 * local_170 * *(float *)(local_208 + 0x120) *
                             *(float *)(local_208 + 0x120)) * local_210;
        }
        local_d4 = local_174;
        local_d0 = local_170;
        local_cc = local_16c;
        pfVar4 = (float *)FUN_004462d0(local_2f8,local_210);
        local_174 = *pfVar4;
        local_170 = pfVar4[1];
        local_16c = pfVar4[2];
        local_8c = local_174;
        local_88 = local_170;
        local_84 = local_16c;
        fVar6 = (float10)FUN_004428b0();
        local_238 = (float)fVar6;
        if ((25.0 < local_238) && (*(int *)(local_20c + 4) == 0)) {
          FUN_008245f0(*(undefined4 *)(local_208 + 0xf4),0);
        }
        puVar3 = (undefined4 *)FUN_00440300();
        local_18c = *puVar3;
        local_188 = puVar3[1];
        local_184 = puVar3[2];
        local_104 = local_18c;
        local_100 = local_188;
        local_fc = local_184;
        puVar3 = (undefined4 *)FUN_004440d0();
        local_1b0 = *puVar3;
        local_1ac = puVar3[1];
        local_1a8 = puVar3[2];
        fVar6 = (float10)FUN_004428b0(&local_14,&local_14);
        local_230 = (float)fVar6;
        pfVar4 = (float *)FUN_004462d0(local_298,0.2 / local_230);
        local_168 = *pfVar4;
        local_164 = pfVar4[1];
        local_160 = pfVar4[2];
        local_a4 = local_168;
        local_a0 = local_164;
        local_9c = local_160;
      }
      else {
        local_21c = *(float *)(local_208 + 0x114);
        local_220 = *(float *)(local_20c + 8);
        local_18c = *(undefined4 *)(local_20c + 0x20);
        local_188 = *(undefined4 *)(local_20c + 0x24);
        local_184 = *(undefined4 *)(local_20c + 0x28);
        puVar3 = (undefined4 *)
                 FUN_00459570(local_310,local_21c,local_174,local_170,local_16c,local_220);
        local_1bc = *puVar3;
        local_1b8 = puVar3[1];
        local_1b4 = puVar3[2];
        puVar3 = (undefined4 *)FUN_004462d0(local_2b0,1.0 / (local_21c + local_220));
        local_198 = *puVar3;
        local_194 = puVar3[1];
        local_190 = puVar3[2];
        local_20 = local_198;
        local_1c = local_194;
        local_18 = local_190;
        pfVar4 = (float *)FUN_004401a0(local_34c,local_174,local_170,local_16c);
        local_174 = *pfVar4;
        local_170 = pfVar4[1];
        local_16c = pfVar4[2];
        local_2c = local_174;
        local_28 = local_170;
        local_24 = local_16c;
        fVar6 = (float10)FUN_004428b0(&local_180,&local_174);
        local_244 = (float)fVar6;
        pfVar4 = (float *)FUN_00459570(local_2c8,0x3f000000,local_174,local_170,local_16c,-local_244
                                      );
        local_174 = *pfVar4;
        local_170 = pfVar4[1];
        local_16c = pfVar4[2];
        local_38 = local_174;
        local_34 = local_170;
        local_30 = local_16c;
        fVar6 = (float10)FUN_004428b0();
        local_234 = (float)fVar6;
        if (local_234 < 25.0) {
          pfVar4 = (float *)FUN_004462d0(local_328,0x40a00000);
          local_174 = *pfVar4;
          local_170 = pfVar4[1];
          local_16c = pfVar4[2];
          local_44 = local_174;
          local_40 = local_170;
          local_3c = local_16c;
        }
        pfVar4 = (float *)FUN_00440130(local_2e0,local_174,local_170,local_16c);
        local_174 = *pfVar4;
        local_170 = pfVar4[1];
        local_16c = pfVar4[2];
        local_68 = local_174;
        local_64 = local_170;
        local_60 = local_16c;
        puVar3 = (undefined4 *)FUN_00440300();
        local_18c = *puVar3;
        local_188 = puVar3[1];
        local_184 = puVar3[2];
        local_80 = local_18c;
        local_7c = local_188;
        local_78 = local_184;
        puVar3 = (undefined4 *)FUN_004440d0();
        local_1a4 = *puVar3;
        local_1a0 = puVar3[1];
        local_19c = puVar3[2];
        fVar6 = (float10)FUN_004428b0(&local_14,&local_14);
        local_240 = (float)fVar6;
        pfVar4 = (float *)FUN_004462d0(local_274,0.2 / local_240);
        local_168 = *pfVar4;
        local_164 = pfVar4[1];
        local_160 = pfVar4[2];
        local_98 = local_168;
        local_94 = local_164;
        local_90 = local_160;
      }
      if ((*(uint *)(*(int *)(local_208 + 0x230) + 0x114) & 0x200) == 0) {
        if (local_168 <= 1.5707964) {
          if (local_168 < -1.5707964) {
            pfVar4 = (float *)FUN_004462d0(local_2a4,-1.5707964 / local_168);
            local_168 = *pfVar4;
            local_164 = pfVar4[1];
            local_160 = pfVar4[2];
            local_c8 = local_168;
            local_c4 = local_164;
            local_c0 = local_160;
          }
        }
        else {
          pfVar4 = (float *)FUN_004462d0(local_28c,1.5707964 / local_168);
          local_168 = *pfVar4;
          local_164 = pfVar4[1];
          local_160 = pfVar4[2];
          local_b0 = local_168;
          local_ac = local_164;
          local_a8 = local_160;
        }
        if (local_164 <= 3.1415927) {
          if (local_164 < -3.1415927) {
            pfVar4 = (float *)FUN_004462d0(local_2d4,-3.1415927 / local_164);
            local_168 = *pfVar4;
            local_164 = pfVar4[1];
            local_160 = pfVar4[2];
            local_f8 = local_168;
            local_f4 = local_164;
            local_f0 = local_160;
          }
        }
        else {
          pfVar4 = (float *)FUN_004462d0(local_2bc,3.1415927 / local_164);
          local_168 = *pfVar4;
          local_164 = pfVar4[1];
          local_160 = pfVar4[2];
          local_e0 = local_168;
          local_dc = local_164;
          local_d8 = local_160;
        }
        if (local_160 <= 0.7853982) {
          if (local_160 < -0.7853982) {
            pfVar4 = (float *)FUN_004462d0(local_304,-0.7853982 / local_160);
            local_168 = *pfVar4;
            local_164 = pfVar4[1];
            local_160 = pfVar4[2];
            local_ec = local_168;
            local_e8 = local_164;
            local_e4 = local_160;
          }
        }
        else {
          pfVar4 = (float *)FUN_004462d0(local_2ec,0.7853982 / local_160);
          local_168 = *pfVar4;
          local_164 = pfVar4[1];
          local_160 = pfVar4[2];
          local_110 = local_168;
          local_10c = local_164;
          local_108 = local_160;
        }
        puVar3 = (undefined4 *)
                 FUN_00440130(local_31c,*(undefined4 *)(local_208 + 0x138),
                              *(undefined4 *)(local_208 + 0x13c),*(undefined4 *)(local_208 + 0x140))
        ;
        local_5c = *puVar3;
        local_58 = puVar3[1];
        local_54 = puVar3[2];
        *(undefined4 *)(local_208 + 0x138) = local_5c;
        *(undefined4 *)(local_208 + 0x13c) = local_58;
        *(undefined4 *)(local_208 + 0x140) = local_54;
      }
      *(float *)(local_208 + 300) = local_174;
      *(float *)(local_208 + 0x130) = local_170;
      *(float *)(local_208 + 0x134) = local_16c;
      fVar6 = (float10)FUN_0045c420();
      local_218 = (float)fVar6;
      *(float *)(local_208 + 0x11c) = local_218;
      if (local_218 <= 0.0) {
        local_228 = 1e+30;
      }
      else {
        local_228 = 1.0 / local_218;
      }
      *(float *)(local_208 + 0x120) = local_228;
      *(double *)(*(int *)(local_208 + 0xf4) + 0x48) =
           (double)(local_214 * local_174) + *(double *)(*(int *)(local_208 + 0xf4) + 0x48);
      *(double *)(*(int *)(local_208 + 0xf4) + 0x50) =
           (double)(local_214 * local_170) + *(double *)(*(int *)(local_208 + 0xf4) + 0x50);
      *(double *)(*(int *)(local_208 + 0xf4) + 0x58) =
           (double)(local_214 * local_16c) + *(double *)(*(int *)(local_208 + 0xf4) + 0x58);
      puVar3 = (undefined4 *)
               FUN_00444d50(local_3a4,*(int *)(local_208 + 0xf4) + 0x20,
                            *(undefined4 *)(local_208 + 0x138));
      puVar5 = local_15c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_15c;
      puVar5 = (undefined4 *)(*(int *)(local_208 + 0xf4) + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

