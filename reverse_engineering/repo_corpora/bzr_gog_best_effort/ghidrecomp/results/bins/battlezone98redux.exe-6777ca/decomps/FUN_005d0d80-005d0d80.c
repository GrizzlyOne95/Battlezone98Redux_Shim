
void FUN_005d0d80(float param_1)

{
  char cVar1;
  undefined4 *puVar2;
  float *pfVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined1 local_1b0 [48];
  undefined1 local_180 [4];
  undefined4 *local_17c;
  undefined1 local_178 [4];
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  int local_150;
  int local_14c;
  int local_148;
  uint local_144;
  int local_140;
  undefined4 local_13c [16];
  undefined4 local_fc [16];
  float local_bc;
  float local_b8;
  float local_b4;
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
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_005d0cc0();
  if (*(int *)(local_148 + 0x238) != 0) {
    local_14c = *(int *)(local_148 + 0xf4) + 0x20;
    puVar2 = (undefined4 *)FUN_008203f0();
    puVar7 = local_13c;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar2 = local_13c;
    puVar7 = local_fc;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar7 = puVar7 + 1;
    }
    iVar6 = *(int *)(local_148 + 0xf8);
    local_80 = *(float *)(iVar6 + 0x160);
    local_7c = *(float *)(iVar6 + 0x164);
    local_78 = *(float *)(iVar6 + 0x168);
    local_74 = *(float *)(iVar6 + 0x16c);
    local_70 = *(float *)(iVar6 + 0x170);
    local_6c = *(float *)(iVar6 + 0x174);
    local_68[0] = local_80;
    local_68[1] = local_7c;
    local_68[2] = local_78;
    local_68[3] = local_74;
    local_68[4] = local_7c;
    local_68[5] = local_78;
    local_68[6] = local_80;
    local_68[7] = local_7c;
    local_68[8] = local_6c;
    local_68[9] = local_74;
    local_68[10] = local_7c;
    local_68[0xb] = local_6c;
    local_68[0xc] = local_80;
    local_68[0xd] = local_70;
    local_68[0xe] = local_78;
    local_68[0xf] = local_74;
    local_68[0x10] = local_70;
    local_68[0x11] = local_78;
    local_68[0x12] = local_80;
    local_68[0x13] = local_70;
    local_68[0x14] = local_6c;
    local_68[0x15] = local_74;
    local_68[0x16] = local_70;
    local_68[0x17] = local_6c;
    FUN_00820180();
    local_15c = 1e+30;
    local_170 = 1e+30;
    local_168 = -1e+30;
    local_164 = -1e+30;
    for (local_144 = 0; local_144 < 8; local_144 = local_144 + 1) {
      if (local_68[local_144 * 3] <= local_15c && local_15c != local_68[local_144 * 3]) {
        local_15c = local_68[local_144 * 3];
      }
      if (local_168 < local_68[local_144 * 3]) {
        local_168 = local_68[local_144 * 3];
      }
      if (local_68[local_144 * 3 + 2] <= local_170 && local_170 != local_68[local_144 * 3 + 2]) {
        local_170 = local_68[local_144 * 3 + 2];
      }
      if (local_164 < local_68[local_144 * 3 + 2]) {
        local_164 = local_68[local_144 * 3 + 2];
      }
    }
    FUN_005b2950((double)local_15c,(double)local_170,(double)local_168,(double)local_164,local_1b0);
    while (cVar1 = FUN_00462710(&local_17c), cVar1 != '\0') {
      local_150 = FUN_004da060(*local_17c);
      if (local_150 != 0) {
        pfVar3 = (float *)(**(code **)(*(int *)(local_150 + 0x18) + 0xc))();
        local_98 = *pfVar3;
        local_94 = pfVar3[1];
        local_90 = pfVar3[2];
        FUN_00820180();
        if (((local_80 < local_98) && (local_98 < local_74)) &&
           ((local_7c < local_94 &&
            (((local_94 < local_70 && (local_78 < local_90)) && (local_90 < local_6c)))))) {
          pfVar3 = (float *)FUN_004624b0();
          local_a4 = *pfVar3;
          local_a0 = pfVar3[1];
          local_9c = pfVar3[2];
          local_16c = param_1 * *(float *)(*(int *)(local_148 + 0xf8) + 0x178);
          local_154 = param_1 * *(float *)(*(int *)(local_148 + 0xf8) + 0x17c);
          local_bc = *(float *)(local_14c + 0x18) * local_16c - local_a4 * local_154;
          local_b8 = *(float *)(local_14c + 0x1c) * local_16c - local_a0 * local_154;
          local_b4 = *(float *)(local_14c + 0x20) * local_16c - local_9c * local_154;
          FUN_004a75b0(&local_bc);
        }
      }
    }
    FUN_0042d8c0(local_178);
    while( true ) {
      uVar4 = FID_conflict_begin(local_180);
      cVar1 = FUN_00420f10(uVar4);
      if (cVar1 == '\0') break;
      FUN_00438c10();
      piVar5 = (int *)FUN_0042de50();
      local_140 = *piVar5;
      local_8c = (float)*(double *)(*(int *)(local_140 + 0x14) + 0x48);
      local_88 = (float)*(double *)(*(int *)(local_140 + 0x14) + 0x50);
      local_84 = (float)*(double *)(*(int *)(local_140 + 0x14) + 0x58);
      FUN_00820180();
      if ((((local_80 < local_8c) && (local_8c < local_74)) && (local_7c < local_88)) &&
         (((local_88 < local_70 && (local_78 < local_84)) && (local_84 < local_6c)))) {
        local_b0 = *(float *)(local_140 + 0x30);
        local_ac = *(float *)(local_140 + 0x34);
        local_a8 = *(float *)(local_140 + 0x38);
        local_158 = param_1 * *(float *)(*(int *)(local_148 + 0xf8) + 0x180);
        local_160 = param_1 * *(float *)(*(int *)(local_148 + 0xf8) + 0x184);
        *(float *)(local_140 + 0x30) =
             (*(float *)(local_14c + 0x18) * local_158 - local_b0 * local_160) +
             *(float *)(local_140 + 0x30);
        *(float *)(local_140 + 0x34) =
             (*(float *)(local_14c + 0x1c) * local_158 - local_ac * local_160) +
             *(float *)(local_140 + 0x34);
        *(float *)(local_140 + 0x38) =
             (*(float *)(local_14c + 0x20) * local_158 - local_a8 * local_160) +
             *(float *)(local_140 + 0x38);
        fVar8 = (float10)FUN_0045c420(*(undefined4 *)(local_140 + 0x30),
                                      *(undefined4 *)(local_140 + 0x34),
                                      *(undefined4 *)(local_140 + 0x38));
        *(float *)(local_140 + 0x20) = (float)fVar8;
        if (*(float *)(local_140 + 0x20) == 0.0) {
          local_174 = 1e+30;
        }
        else {
          local_174 = 1.0 / *(float *)(local_140 + 0x20);
        }
        *(float *)(local_140 + 0x24) = local_174;
      }
    }
  }
  FUN_0047fcb0(param_1);
  FUN_0083e885();
  return;
}

