
void FUN_00587b90(int param_1,int param_2)

{
  float fVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_3c [12];
  int local_30;
  float local_2c;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00915567 == '\0') {
    local_30 = 10;
  }
  else {
    local_30 = 0x19;
  }
  local_28 = local_30;
  fVar3 = (float10)FUN_00822d60();
  local_2c = (float)fVar3;
  local_20 = 0.0;
  local_1c = 0.0;
  local_24 = (DAT_009c91d0 * local_2c) / *(float *)(local_18 + 0x40);
  if (DAT_00915567 == '\0') {
    fVar1 = local_24;
    if ((local_28 <= param_2) &&
       (fVar1 = local_1c,
       (*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) - local_28 <= param_2)) {
      fVar1 = -local_24;
    }
    local_1c = fVar1;
    if (param_1 < local_28) {
      local_20 = -local_24;
    }
    else if ((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) - local_28 <= param_1) {
      local_20 = local_24;
    }
  }
  if ((local_20 == 0.0) && (local_1c == 0.0)) {
    if (*(int *)(local_18 + 0x3c) != 0) {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_18 + 0x3c) + 0x18) + 0xc))();
      *(undefined4 *)(local_18 + 0x44) = *puVar2;
      *(undefined4 *)(local_18 + 0x48) = puVar2[1];
      *(undefined4 *)(local_18 + 0x4c) = puVar2[2];
      puVar2 = (undefined4 *)FUN_00462490();
      *(undefined4 *)(local_18 + 0x50) = *puVar2;
      *(undefined4 *)(local_18 + 0x54) = puVar2[1];
      *(undefined4 *)(local_18 + 0x58) = puVar2[2];
      *(undefined4 *)(local_18 + 0x54) = 0;
      puVar2 = (undefined4 *)FUN_004621a0(local_3c,local_18 + 0x50);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      *(undefined4 *)(local_18 + 0x50) = local_14;
      *(undefined4 *)(local_18 + 0x54) = local_10;
      *(undefined4 *)(local_18 + 0x58) = local_c;
    }
  }
  else {
    *(undefined4 *)(local_18 + 0x3c) = 0;
    fVar3 = (float10)FUN_00447ed0(local_1c * *(float *)(local_18 + 0x50) +
                                  *(float *)(local_18 + 0x44) +
                                  local_20 * *(float *)(local_18 + 0x58),DAT_0091738c,DAT_00917394);
    *(float *)(local_18 + 0x44) = (float)fVar3;
    fVar3 = (float10)FUN_00447ed0((local_1c * *(float *)(local_18 + 0x58) +
                                  *(float *)(local_18 + 0x4c)) -
                                  local_20 * *(float *)(local_18 + 0x50),DAT_00917390,DAT_00917388);
    *(float *)(local_18 + 0x4c) = (float)fVar3;
  }
  if (DAT_009198f2 == '\0') {
    if (DAT_009198f0 == '\0') {
      if ((DAT_009198f1 != '\0') &&
         (*(float *)(local_18 + 0x40) =
               *(float *)(local_18 + 0x40) - local_2c * 0.5 * *(float *)(local_18 + 0x40),
         *(float *)(local_18 + 0x40) <= 2.0 && *(float *)(local_18 + 0x40) != 2.0)) {
        *(undefined4 *)(local_18 + 0x40) = 0x40000000;
      }
    }
    else {
      *(float *)(local_18 + 0x40) =
           local_2c * 0.5 * *(float *)(local_18 + 0x40) + *(float *)(local_18 + 0x40);
      if (8.0 < *(float *)(local_18 + 0x40)) {
        *(undefined4 *)(local_18 + 0x40) = 0x41000000;
      }
    }
  }
  else {
    *(undefined4 *)(local_18 + 0x40) = 0x40800000;
  }
  FUN_0083e885();
  return;
}

