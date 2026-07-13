
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00776690(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_21c [64];
  undefined1 local_1dc [64];
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  uint local_188;
  float local_184;
  float local_180;
  int local_17c;
  float local_178;
  float local_174;
  float local_170;
  char *local_16c;
  float local_168;
  uint local_164;
  uint local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  uint local_14c;
  uint local_148;
  uint local_144;
  float local_140;
  uint local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  char *local_124;
  char *local_120;
  int local_11c;
  undefined4 local_118 [16];
  undefined4 local_d8 [16];
  char local_98 [64];
  char local_58 [64];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if (iVar1 != 0) {
    DAT_00945498 = 1;
    DAT_02c06670 = 0;
    _DAT_02c06674 = 0.0;
    memset(&DAT_02c05b70,0,0xb00);
    FUN_00685fa0();
    local_120 = s_Stars_008f0494;
    fVar4 = (float10)FUN_00787b60(s_Stars_008f0494,"Radius",0x447a0000);
    _DAT_02c06674 = (float)fVar4;
    for (local_11c = 0; local_11c < 0x40; local_11c = local_11c + 1) {
      local_124 = &DAT_02c05b70 + DAT_02c06670 * 0x2c;
      sprintf(local_18,"Texture%02d");
      FUN_00787a30();
      if (*local_124 != '\0') {
        local_144 = 0xff;
        local_14c = 0xff;
        local_13c = 0xff;
        local_154 = 0xff;
        sprintf(local_18,"Color%02d");
        FUN_00787a30(local_120,local_18,"\"255 255 255 255\"",local_98,0x40);
        iVar1 = sscanf(local_98,"\"%d %d %d %d\"",&local_144,&local_14c,&local_13c);
        if (iVar1 < 1) {
          sscanf(local_98,"%d %d %d %d",&local_144,&local_14c,&local_13c);
        }
        *(uint *)(local_124 + 0x10) =
             local_154 << 0x18 | (local_144 & 0xff) << 0x10 | (local_14c & 0xff) << 8 |
             local_13c & 0xff;
        sprintf(local_18,"Size%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0x42c80000);
        local_168 = (float)fVar4;
        *(float *)(local_124 + 0x18) = local_168;
        *(float *)(local_124 + 0x14) = local_168;
        sprintf(local_18,"Width%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,*(undefined4 *)(local_124 + 0x14));
        *(float *)(local_124 + 0x14) = (float)fVar4;
        sprintf(local_18,"Height%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,*(undefined4 *)(local_124 + 0x18));
        *(float *)(local_124 + 0x18) = (float)fVar4;
        sprintf(local_18,"Azimuth%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0);
        local_18c = (float)fVar4;
        *(float *)(local_124 + 0x1c) = local_18c * 0.017453292;
        sprintf(local_18,"Elevation%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0x42340000);
        local_194 = (float)fVar4;
        *(float *)(local_124 + 0x20) = local_194 * -0.017453292;
        sprintf(local_18,"Roll%02d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0,&DAT_02cc40c0);
        local_198 = (float)fVar4;
        *(float *)(local_124 + 0x24) = local_198 * -0.017453292;
        puVar2 = (undefined4 *)
                 FUN_0081ee70(local_1dc,*(undefined4 *)(local_124 + 0x20),
                              *(undefined4 *)(local_124 + 0x1c),*(undefined4 *)(local_124 + 0x24),0,
                              0,0);
        puVar3 = local_d8;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        FUN_00686070();
        FUN_00777320();
        FUN_00686230();
        DAT_02c06670 = DAT_02c06670 + 1;
      }
    }
    local_120 = s_StarList_008f0488;
    local_17c = FUN_00787ac0(s_StarList_008f0488,"Solid",0);
    fVar4 = (float10)FUN_00787b60(local_120,"LayerHeight",0x41f00000);
    local_190 = (float)fVar4;
    local_170 = local_190 * -0.017453292;
    FUN_00787a30(local_120,"Texture",&DAT_008a1ad8,&DAT_02c05b70 + DAT_02c06670 * 0x2c,0x10);
    if ((&DAT_02c05b70)[DAT_02c06670 * 0x2c] != '\0') {
      fVar4 = (float10)FUN_00787b60(local_120,"Radius",0x447a0000);
      local_140 = (float)fVar4;
      if (local_17c == 0) {
        local_16c = &DAT_02c05b70 + DAT_02c06670 * 0x2c;
      }
      else {
        local_16c = "Untextured";
      }
      FUN_00686070();
      local_178 = 0.7853981;
      local_134 = local_170 * 0.5;
      local_11c = 0;
      while ((local_11c < 9 && (DAT_02c06670 < 0x40))) {
        local_164 = 0xff;
        local_160 = 0xff;
        local_148 = 0xff;
        local_15c = 0xff;
        sprintf(local_18,"Color%02d");
        FUN_00787a30(local_120,local_18,"\"255 255 255 255\"",local_58,0x40);
        iVar1 = sscanf(local_58,"\"%d %d %d %d\"",&local_164,&local_160,&local_148);
        if (iVar1 < 1) {
          sscanf(local_58,"%d %d %d %d",&local_164,&local_160,&local_148);
        }
        local_188 = local_15c << 0x18 | (local_164 & 0xff) << 0x10 | (local_160 & 0xff) << 8 |
                    local_148 & 0xff;
        sprintf(local_18,"Size%d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0x42c80000);
        local_138 = (float)fVar4;
        local_12c = local_138;
        sprintf(local_18,"Width%d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,local_138);
        local_138 = (float)fVar4;
        sprintf(local_18,"Height%d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,local_12c);
        local_12c = (float)fVar4;
        sprintf(local_18,"Start%d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0);
        local_184 = (float)fVar4;
        local_128 = local_184 * 0.017453292;
        sprintf(local_18,"End%d");
        fVar4 = (float10)FUN_00787b60(local_120,local_18,0x43b40000);
        local_180 = (float)fVar4;
        local_19c = local_180 * 0.017453292;
        sprintf(local_18,"Count%d");
        local_150 = FUN_00787ac0(local_120,local_18,0xffffffff);
        if (0 < local_150) {
          local_130 = 0.0;
          local_174 = (local_19c - local_128) / (float)local_150;
          local_128 = local_174 * 0.5 + local_128;
          local_158 = 0;
          for (; (local_158 < local_150 && (DAT_02c06670 < 0x40)); DAT_02c06670 = DAT_02c06670 + 1)
          {
            puVar2 = (undefined4 *)FUN_0081ee70(local_21c,local_134,local_128,local_130,0,0,0);
            puVar3 = local_118;
            for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar3 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar3 = puVar3 + 1;
            }
            FUN_00777320(0,local_118,(local_138 * 0.5) / local_140,(local_12c * 0.5) / local_140,
                         0x3f800000);
            (&DAT_02c05b84)[DAT_02c06670 * 0xb] = local_138;
            (&DAT_02c05b88)[DAT_02c06670 * 0xb] = local_12c;
            (&DAT_02c05b8c)[DAT_02c06670 * 0xb] = local_128;
            (&DAT_02c05b90)[DAT_02c06670 * 0xb] = local_134;
            (&DAT_02c05b94)[DAT_02c06670 * 0xb] = local_130;
            *(float *)(DAT_02c06670 * 0x2c + 0x2c05b98) = local_140;
            local_128 = local_128 + local_174;
            local_130 = local_130 + local_178;
            local_158 = local_158 + 1;
          }
        }
        local_134 = local_134 + local_170;
        local_11c = local_11c + 1;
      }
      FUN_00686230();
    }
    FUN_00686250();
    if (DAT_02c06670 < 1) {
      DAT_02c06670 = 0;
    }
  }
  FUN_0083e885();
  return;
}

