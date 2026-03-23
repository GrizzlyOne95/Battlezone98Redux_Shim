
void FUN_0045b050(int param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_1d0 [76];
  undefined1 local_184 [24];
  undefined1 local_16c [12];
  float local_160;
  float local_15c;
  float local_158;
  undefined4 local_154;
  undefined4 local_150;
  float local_14c;
  undefined4 local_148;
  undefined4 local_144;
  float local_140;
  float local_13c;
  undefined4 local_138;
  int local_134;
  float local_130;
  undefined4 local_12c;
  float local_128;
  undefined1 local_122;
  undefined1 local_121;
  int local_120;
  undefined4 local_11c [16];
  undefined4 local_dc [16];
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  uint local_84;
  float local_80;
  float local_7c;
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
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008470ae;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_148 = FUN_00439e60(local_14);
  FUN_0044b810();
  if (*(float *)(param_1 + 0x60) <= param_2 && param_2 != *(float *)(param_1 + 0x60)) {
    puVar1 = (undefined4 *)
             FUN_006897e0(local_16c,local_148,*(undefined8 *)(param_1 + 0xa8),
                          *(undefined8 *)(param_1 + 0xb0),*(undefined8 *)(param_1 + 0xb8));
    local_74 = *puVar1;
    local_70 = puVar1[1];
    local_6c = puVar1[2];
    local_50 = local_74;
    local_4c = local_70;
    local_48 = local_6c;
    fVar6 = (float10)FUN_004428b0(&local_74,&local_74);
    local_160 = (float)fVar6;
    if (*(float *)(local_120 + 0x1b4) * *(float *)(local_120 + 0x1b4) < local_160) {
      *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x80);
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x84);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x88);
      *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x8c);
      *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0xa8);
      *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0xac);
      *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0xb0);
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0xbc);
      goto LAB_0045b742;
    }
    if (param_2 == 0.0) {
      local_130 = 1e+30;
    }
    else {
      local_130 = 1.0 / param_2;
    }
    local_128 = local_130;
    local_2c = (float)(*(double *)(param_1 + 0xa8) - *(double *)(param_1 + 0x90)) * local_130;
    local_28 = (float)(*(double *)(param_1 + 0xb0) - *(double *)(param_1 + 0x98)) * local_130;
    local_24 = (float)(*(double *)(param_1 + 0xb8) - *(double *)(param_1 + 0xa0)) * local_130;
    iVar2 = get();
    local_122 = iVar2 == 0;
    local_121 = local_122;
    if ((bool)local_122) {
      local_2c = 0.0;
      local_28 = 0.0;
      local_24 = 0.0;
LAB_0045b2e8:
      local_134 = FUN_00459620();
      local_8 = 0;
      if (local_134 == 0) {
        local_12c = 0;
      }
      else {
        local_12c = FUN_00459660();
      }
      local_144 = local_12c;
      local_8 = 0xffffffff;
      local_150 = local_12c;
      FUN_0045bb10();
    }
    else {
      uVar3 = FUN_00822a60();
      if ((uVar3 & 7) == 0) goto LAB_0045b2e8;
    }
    local_154 = get();
    puVar1 = (undefined4 *)FUN_0045bb80();
    local_138 = *puVar1;
    do {
      uVar3 = get();
      if (0x3ff < uVar3) {
        FUN_007d6a70();
        break;
      }
      puVar1 = (undefined4 *)
               FUN_0044ba00(local_1d0,param_1 + 0x70,param_1 + 0x90,param_1 + 0x80,param_1 + 0xa8,
                            *(float *)(param_1 + 0x60) * local_128);
      puVar5 = local_11c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar1 = local_11c;
      puVar5 = local_dc;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar5 = puVar5 + 1;
      }
      pfVar4 = (float *)FUN_00440300();
      local_68 = *pfVar4;
      local_64 = pfVar4[1];
      local_60 = pfVar4[2];
      local_20 = *(float *)(local_120 + 0x18c);
      local_38 = local_68;
      local_34 = local_64;
      local_30 = local_60;
      fVar6 = (float10)FUN_004464c0();
      local_14c = (float)fVar6;
      local_20 = *(float *)(local_120 + 0x1a4) * local_38 +
                 local_14c * *(float *)(local_120 + 0x198) + local_20;
      local_1c = *(float *)(local_120 + 400);
      fVar6 = (float10)FUN_004464c0();
      local_15c = (float)fVar6;
      local_1c = *(float *)(local_120 + 0x1a8) * local_34 +
                 local_15c * *(float *)(local_120 + 0x19c) + local_1c;
      local_18 = *(float *)(local_120 + 0x194);
      fVar6 = (float10)FUN_004464c0();
      local_140 = (float)fVar6;
      local_18 = *(float *)(local_120 + 0x1ac) * local_30 +
                 local_140 * *(float *)(local_120 + 0x1a0) + local_18;
      puVar1 = (undefined4 *)FUN_00440210();
      local_44 = *puVar1;
      local_40 = puVar1[1];
      local_3c = puVar1[2];
      local_20 = (float)local_44;
      local_1c = (float)local_40;
      local_18 = (float)local_3c;
      FUN_00459600();
      puVar1 = (undefined4 *)FUN_00439de0(local_184);
      local_9c = *puVar1;
      local_98 = puVar1[1];
      local_94 = puVar1[2];
      local_90 = local_20;
      local_8c = local_1c;
      local_88 = local_18;
      local_84 = *(uint *)(param_1 + 0x60) ^ 0x80000000;
      local_5c = local_9c;
      local_58 = local_98;
      local_54 = local_94;
      fVar6 = (float10)FUN_004464c0();
      local_13c = (float)fVar6;
      local_80 = local_13c * *(float *)(local_120 + 0x17c);
      fVar6 = (float10)FUN_004588c0();
      local_7c = (float)fVar6;
      FUN_0045b950();
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + *(float *)(local_120 + 0x184);
      fVar6 = (float10)FUN_004464c0();
      local_158 = (float)fVar6;
      *(float *)(param_1 + 0x60) =
           local_158 * *(float *)(local_120 + 0x188) + *(float *)(param_1 + 0x60);
    } while (*(float *)(param_1 + 0x60) <= param_2 && param_2 != *(float *)(param_1 + 0x60));
  }
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x80);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x84);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x88);
  *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0xa8);
  *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0xac);
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0xb0);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0xb8);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0xbc);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - param_2;
LAB_0045b742:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

