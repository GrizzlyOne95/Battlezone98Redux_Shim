
void FUN_005af160(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1b8 [24];
  float local_1a0;
  float local_19c;
  ushort *local_198;
  int *local_194;
  ushort local_190;
  int local_18c;
  int local_188;
  int local_184;
  int local_180;
  int local_17c;
  int local_178;
  int local_174;
  int local_170;
  uint local_16c;
  float *local_168;
  int local_164;
  int *local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150 [16];
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined4 local_90 [4];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004723b0();
  local_164 = 0;
  (**(code **)(*local_160 + 0xac))();
  if ((*(int *)(local_160[0xc0] + 0x1c) == 2) || (*(int *)(local_160[0xc0] + 0x14) == 0x54555252)) {
    local_164 = FUN_004e1190(local_90,local_160[0x5d]);
    local_168 = (float *)FUN_0049c560();
    local_38[0] = *local_168;
    local_38[1] = 0.0;
    local_38[2] = local_168[2];
    local_38[3] = *local_168;
    local_38[4] = 0.0;
    local_38[5] = local_168[5];
    local_38[6] = local_168[3];
    local_38[7] = 0.0;
    local_38[8] = local_168[5];
    local_38[9] = local_168[3];
    local_38[10] = 0.0;
    local_38[0xb] = local_168[2];
    FUN_00820180(local_38);
    local_188 = 0x7fffffff;
    local_18c = 0x7fffffff;
    local_170 = -0x80000000;
    local_178 = -0x80000000;
    for (local_16c = 0; local_16c < 4; local_16c = local_16c + 1) {
      local_180 = (int)(local_38[local_16c * 3] * DAT_02cc50e4);
      local_17c = (int)(local_38[local_16c * 3 + 2] * DAT_02cc50e4);
      if (local_180 < local_188) {
        local_188 = local_180;
      }
      if (local_170 < local_180) {
        local_170 = local_180;
      }
      if (local_17c < local_18c) {
        local_18c = local_17c;
      }
      if (local_178 < local_17c) {
        local_178 = local_17c;
      }
    }
    local_190 = FUN_00453d10();
    for (local_184 = local_18c; local_184 <= local_178 + 1; local_184 = local_184 + 1) {
      for (local_174 = local_188; local_174 <= local_170 + 1; local_174 = local_174 + 1) {
        local_198 = (ushort *)FUN_00492d60();
        *local_198 = *local_198 & 0xf000 | local_190;
      }
    }
    FUN_00777730(local_188);
  }
  else {
    fVar4 = (float10)FUN_004464c0();
    local_19c = (float)fVar4;
    fVar4 = (float10)FUN_004464c0();
    local_1a0 = (float)fVar4;
    puVar1 = (undefined4 *)FUN_0081ed60();
    puVar3 = local_150;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_150;
    puVar3 = local_110;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_0081fe60();
    puVar3 = local_d0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_d0;
    puVar3 = local_90;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_004560b0();
    local_15c = *puVar1;
    local_158 = puVar1[1];
    local_154 = puVar1[2];
    puVar1 = (undefined4 *)FUN_004462d0(local_1b8,0x41c80000);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    iVar2 = local_160[0x3d];
    local_90[0] = *(undefined4 *)(iVar2 + 0x20);
    local_90[1] = *(undefined4 *)(iVar2 + 0x24);
    local_90[2] = *(undefined4 *)(iVar2 + 0x28);
    iVar2 = local_160[0x3d];
    local_90[3] = *(undefined4 *)(iVar2 + 0x2c);
    local_80 = *(undefined4 *)(iVar2 + 0x30);
    local_7c = *(undefined4 *)(iVar2 + 0x34);
    iVar2 = local_160[0x3d];
    local_78 = *(undefined4 *)(iVar2 + 0x38);
    local_74 = *(undefined4 *)(iVar2 + 0x3c);
    local_70 = *(undefined4 *)(iVar2 + 0x40);
    local_44 = local_50;
    local_40 = local_4c;
    local_3c = local_48;
    local_164 = FUN_004e1190(local_90,local_160[0x5d]);
    FUN_0046fb20();
    if (*(int *)(local_160[0xc0] + 0x1c) == 3) {
      FUN_0046fc40();
      *(uint *)(*(int *)(local_164 + 0x228) + 0x114) =
           *(uint *)(*(int *)(local_164 + 0x228) + 0x114) | 0xc;
    }
  }
  iVar2 = FUN_00572a70();
  if (iVar2 != 0) {
    FUN_004b8460();
  }
  local_194 = (int *)FUN_0045ca50();
  (**(code **)(*local_194 + 0x1c))();
  FUN_004376c0(local_160[0x3e] + 0x640);
  local_160[0xc0] = 0;
  FUN_0083e885();
  return;
}

