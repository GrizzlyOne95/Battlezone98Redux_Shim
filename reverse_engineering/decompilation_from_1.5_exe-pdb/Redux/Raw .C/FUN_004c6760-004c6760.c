
void __thiscall FUN_004c6760(int param_1,int param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float fVar4;
  float local_14;
  float local_10;
  
  fVar3 = (float10)FUN_00822d60(10);
  fVar1 = (float)fVar3;
  local_14 = 0.0;
  local_10 = 0.0;
  fVar4 = (DAT_0099235c * fVar1) / *(float *)(param_1 + 0x44);
  fVar2 = fVar4;
  if ((9 < param_3) &&
     (fVar2 = local_10,
     (*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + -10 <= param_3)) {
    fVar2 = -fVar4;
  }
  local_10 = fVar2;
  if (param_2 < 10) {
    local_14 = -fVar4;
  }
  else if ((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) + -10 <= param_2) {
    local_14 = fVar4;
  }
  if (DAT_00919856 != '\0') {
    local_14 = -fVar4;
  }
  if (DAT_00919857 != '\0') {
    local_14 = fVar4;
  }
  if (DAT_00919858 != '\0') {
    local_10 = fVar4;
  }
  if (DAT_00919859 != '\0') {
    local_10 = -fVar4;
  }
  if ((local_14 != 0.0) || (local_10 != 0.0)) {
    *(float *)(param_1 + 0x48) =
         local_10 * *(float *)(param_1 + 0x54) + local_14 * *(float *)(param_1 + 0x5c) +
         *(float *)(param_1 + 0x48);
    *(float *)(param_1 + 0x50) =
         (local_10 * *(float *)(param_1 + 0x5c) - local_14 * *(float *)(param_1 + 0x54)) +
         *(float *)(param_1 + 0x50);
    fVar3 = (float10)FUN_007855e0((double)*(float *)(param_1 + 0x48),
                                  (double)*(float *)(param_1 + 0x50));
    *(float *)(param_1 + 0x4c) = (float)fVar3;
  }
  if (DAT_009198f2 == '\0') {
    if (DAT_009198f0 == '\0') {
      if ((DAT_009198f1 != '\0') &&
         (*(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) - fVar1 * 0.5 * *(float *)(param_1 + 0x44),
         *(float *)(param_1 + 0x44) <= 1.7 && *(float *)(param_1 + 0x44) != 1.7)) {
        *(undefined4 *)(param_1 + 0x44) = 0x3fd9999a;
      }
    }
    else {
      *(float *)(param_1 + 0x44) =
           fVar1 * 0.5 * *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x44);
      if (16.0 < *(float *)(param_1 + 0x44)) {
        *(undefined4 *)(param_1 + 0x44) = 0x41800000;
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x44) = 0x41000000;
  }
  return;
}

