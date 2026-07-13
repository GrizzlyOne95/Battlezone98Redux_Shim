
void FUN_005f0d90(float param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_608 [408];
  undefined1 local_470 [48];
  undefined1 local_440 [12];
  float local_434;
  float local_430;
  float local_42c;
  undefined4 local_428;
  undefined8 local_424;
  float local_41c;
  float local_418;
  float local_414;
  undefined8 local_410;
  float local_408;
  float local_404;
  int local_400;
  float local_3fc;
  float local_3f8;
  undefined4 *local_3f4;
  float local_3f0;
  int local_3ec;
  undefined4 *local_3e8;
  int local_3e4;
  undefined4 *local_3e0;
  int local_3dc;
  undefined4 local_3d8 [16];
  undefined4 local_398 [16];
  undefined4 local_358 [16];
  undefined4 local_318 [16];
  undefined4 local_2d8 [16];
  undefined4 local_298 [16];
  undefined4 local_258 [16];
  undefined4 local_218 [16];
  undefined4 local_1d8 [16];
  undefined4 local_198 [16];
  undefined4 local_158 [16];
  undefined4 local_118 [16];
  undefined4 local_d8 [16];
  undefined4 local_98;
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
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
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_005f0750();
  if (*(int *)(local_3dc + 0x2c0) != 0) {
    FUN_0046d060();
    FUN_004a7700();
  }
  if ((*(int *)(local_3dc + 0x2c0) == 0) || (*(int *)(local_3dc + 0xfc) == 0)) {
    FUN_005f08c0();
  }
  else {
    FUN_005f07f0();
  }
  local_434 = 1.0 / param_1;
  local_3e0 = (undefined4 *)(*(int *)(local_3dc + 0xf4) + 0x20);
  puVar2 = (undefined4 *)FUN_00447f60();
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  local_44 = puVar2[3];
  local_40 = puVar2[4];
  local_3c = puVar2[5];
  FUN_00444f70(*(undefined4 *)(local_3dc + 0xf0),local_50,local_4c,local_48,local_44,local_40,
               local_3c);
  *(double *)(local_3e0 + 0xc) = (double)local_408;
  fVar5 = (float10)FUN_004e9610();
  local_3fc = (float)fVar5;
  local_418 = *(float *)(*(int *)(local_3dc + 0xf8) + 0x328) * local_3fc;
  local_404 = *(float *)(*(int *)(local_3dc + 0xf8) + 0x32c) * local_3fc;
  local_3f0 = *(float *)(*(int *)(local_3dc + 0xf8) + 0x330) * local_3fc;
  *(float *)(local_3dc + 0x150) = -local_3f0 * *(float *)(local_3dc + 0x138);
  *(float *)(local_3dc + 0x154) = -local_3f0 * *(float *)(local_3dc + 0x13c);
  *(float *)(local_3dc + 0x158) = -local_3f0 * *(float *)(local_3dc + 0x140);
  local_14 = local_98;
  local_10 = local_94 + 2.0;
  local_c = local_90;
  puVar2 = (undefined4 *)FUN_004621a0();
  local_68 = *puVar2;
  local_64 = puVar2[1];
  local_60 = puVar2[2];
  local_14 = local_68;
  local_10 = (float)local_64;
  local_c = local_60;
  puVar2 = (undefined4 *)FUN_004560b0();
  local_80 = *puVar2;
  local_7c = puVar2[1];
  local_78 = puVar2[2];
  local_20 = local_80;
  local_1c = local_7c;
  local_18 = local_78;
  puVar2 = (undefined4 *)FUN_00439d80();
  local_8c = *puVar2;
  local_88 = puVar2[1];
  local_84 = puVar2[2];
  local_2c = local_8c;
  local_28 = local_88;
  local_24 = local_84;
  fVar5 = (float10)FUN_004428b0();
  local_41c = (float)fVar5;
  *(float *)(local_3dc + 0x150) = *(float *)(local_3dc + 0x150) - local_41c * local_404;
  fVar5 = (float10)FUN_004428b0();
  local_430 = (float)fVar5;
  *(float *)(local_3dc + 0x158) = local_430 * local_404 + *(float *)(local_3dc + 0x158);
  puVar2 = (undefined4 *)
           FUN_00439d00(local_440,*(undefined4 *)(local_3dc + 0x138),
                        *(undefined4 *)(local_3dc + 0x13c),*(undefined4 *)(local_3dc + 0x140),
                        param_1 * 0.5);
  local_38 = *puVar2;
  local_34 = puVar2[1];
  local_30 = puVar2[2];
  *(undefined4 *)(local_3dc + 0x138) = local_38;
  *(undefined4 *)(local_3dc + 0x13c) = local_34;
  *(undefined4 *)(local_3dc + 0x140) = local_30;
  puVar2 = (undefined4 *)
           FUN_0081ee70(local_608,-*(float *)(local_3dc + 0x138) * param_1,
                        -*(float *)(local_3dc + 0x13c) * param_1,
                        -*(float *)(local_3dc + 0x140) * param_1,0,0);
  puVar4 = local_158;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_158;
  puVar4 = local_118;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)
           FUN_00439d00(local_470,*(undefined4 *)(local_3dc + 0x138),
                        *(undefined4 *)(local_3dc + 0x13c),*(undefined4 *)(local_3dc + 0x140),
                        param_1 * 0.5);
  local_5c = *puVar2;
  local_58 = puVar2[1];
  local_54 = puVar2[2];
  *(undefined4 *)(local_3dc + 0x138) = local_5c;
  *(undefined4 *)(local_3dc + 0x13c) = local_58;
  *(undefined4 *)(local_3dc + 0x140) = local_54;
  puVar2 = (undefined4 *)FUN_0081fe60();
  puVar4 = local_198;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_198;
  puVar4 = local_3e0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_42c = *(float *)(*(int *)(local_3dc + 0x230) + 0xc4);
  local_428 = *(undefined4 *)(*(int *)(local_3dc + 0x230) + 200);
  local_3f8 = -local_418 * local_42c;
  *(float *)(local_3dc + 0x154) =
       (local_3f8 - *(float *)(local_3dc + 0x2c4)) * local_434 + *(float *)(local_3dc + 0x154);
  *(float *)(local_3dc + 0x2c4) = local_3f8;
  puVar2 = (undefined4 *)FUN_0081ebb0();
  puVar4 = local_218;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_218;
  puVar4 = local_d8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)FUN_008203f0();
  puVar4 = local_258;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_258;
  puVar4 = local_358;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)FUN_0081fe60();
  puVar4 = local_2d8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_2d8;
  puVar4 = local_3e0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  if (*(int *)(local_3dc + 0x2a8) != 0) {
    for (local_3e4 = *(int *)(*(int *)(local_3dc + 0xf4) + 0x80); local_3e4 != 0;
        local_3e4 = *(int *)(local_3e4 + 0x7c)) {
      puVar2 = (undefined4 *)FUN_0081fe60();
      puVar4 = local_3d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_3d8;
      puVar4 = (undefined4 *)(local_3e4 + 0x20);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      FUN_00681a00();
    }
    local_3f4 = (undefined4 *)(*(int *)(local_3dc + 0x2a8) + 0x20);
    puVar2 = (undefined4 *)FUN_0081fe60();
    puVar4 = local_298;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_298;
    puVar4 = local_3f4;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_00681a00();
  }
  if (0 < *(int *)(local_3dc + 700)) {
    local_424 = FUN_008205a0();
    local_6c = (float)((ulonglong)local_424 >> 0x20);
    local_74 = 0;
    local_70 = -(float)local_424;
    local_410 = local_424;
    for (local_3ec = 0; local_3ec < *(int *)(local_3dc + 700); local_3ec = local_3ec + 1) {
      local_400 = *(int *)(local_3dc + 0x2ac + local_3ec * 4);
      local_3e8 = (undefined4 *)(local_400 + 0x20);
      local_414 = *(float *)(local_400 + 0x30) * local_70 + *(float *)(local_400 + 0x34) * local_6c;
      puVar2 = (undefined4 *)FUN_0081ec40();
      puVar4 = local_318;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_318;
      puVar4 = local_398;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = (undefined4 *)FUN_0081fe60();
      puVar4 = local_1d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_1d8;
      puVar4 = local_3e8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      FUN_00681a00();
    }
  }
  *(undefined4 *)(local_3dc + 300) = 0;
  *(undefined4 *)(local_3dc + 0x130) = 0;
  *(undefined4 *)(local_3dc + 0x134) = 0;
  *(undefined4 *)(local_3dc + 0x11c) = 0;
  *(undefined4 *)(local_3dc + 0x144) = 0;
  *(undefined4 *)(local_3dc + 0x148) = 0;
  *(undefined4 *)(local_3dc + 0x14c) = 0;
  *(float *)(local_3dc + 0x280) = *(float *)(*(int *)(local_3dc + 0x230) + 200) * 0.5;
  if ((*(uint *)(*(int *)(local_3dc + 0xf4) + 0x14) & 0x10) == 0) {
LAB_005f1873:
    cVar1 = FUN_004b9830();
    if ((cVar1 == '\0') || ((*(uint *)(*(int *)(local_3dc + 0x230) + 0x114) & 0x1000) == 0))
    goto LAB_005f18cf;
  }
  else {
    iVar3 = FUN_004e96a0();
    if (iVar3 == 0) goto LAB_005f1873;
  }
  *(float *)(local_3dc + 0x280) =
       *(float *)(local_3dc + 0x280) - *(float *)(*(int *)(local_3dc + 0xf4) + 0x3c);
LAB_005f18cf:
  FUN_004ab380();
  FUN_0083e885();
  return;
}

