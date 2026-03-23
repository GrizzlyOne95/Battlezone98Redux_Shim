
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00594290(int param_1)

{
  float fVar1;
  float10 fVar2;
  float fVar3;
  float local_c;
  
  fVar2 = (float10)FUN_00822d60();
  fVar1 = (float)fVar2;
  local_c = (float)((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) + 1) /
            *(float *)(param_1 + 0x38);
  if ((float)((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + 1) <
      *(float *)(param_1 + 0x3c) * local_c) {
    local_c = (float)((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + 1) /
              *(float *)(param_1 + 0x3c);
  }
  if (DAT_009198f2 == '\0') {
    if (DAT_009198f0 == '\0') {
      if (DAT_009198f1 != '\0') {
        *(float *)(param_1 + 0x40) =
             *(float *)(param_1 + 0x40) - fVar1 * 0.5 * *(float *)(param_1 + 0x40);
      }
    }
    else {
      *(float *)(param_1 + 0x40) =
           fVar1 * 0.5 * *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x40);
    }
  }
  else {
    *(float *)(param_1 + 0x40) = local_c;
  }
  if (*(float *)(param_1 + 0x40) <= 100.0) {
    if (*(float *)(param_1 + 0x40) <= local_c && local_c != *(float *)(param_1 + 0x40)) {
      *(float *)(param_1 + 0x40) = local_c;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x40) = 0x42c80000;
  }
  fVar3 = *(float *)(&DAT_008724bc + DAT_00919875 * 4) / *(float *)(param_1 + 0x40);
  *(float *)(param_1 + 0x30) = (float)_DAT_009198e4 * fVar1 * fVar3 + *(float *)(param_1 + 0x30);
  if ((float)DAT_02ce99b0 < *(float *)(param_1 + 0x30) ||
      (float)DAT_02ce99b0 == *(float *)(param_1 + 0x30)) {
    if ((float)DAT_02ce99b8 < *(float *)(param_1 + 0x30)) {
      *(float *)(param_1 + 0x30) = (float)DAT_02ce99b8;
    }
  }
  else {
    *(float *)(param_1 + 0x30) = (float)DAT_02ce99b0;
  }
  *(float *)(param_1 + 0x34) = (float)_DAT_009198dc * fVar1 * fVar3 + *(float *)(param_1 + 0x34);
  if ((float)DAT_02ce99b4 < *(float *)(param_1 + 0x34) ||
      (float)DAT_02ce99b4 == *(float *)(param_1 + 0x34)) {
    if ((float)DAT_02ce99bc < *(float *)(param_1 + 0x34)) {
      *(float *)(param_1 + 0x34) = (float)DAT_02ce99bc;
    }
  }
  else {
    *(float *)(param_1 + 0x34) = (float)DAT_02ce99b4;
  }
  *(int *)(param_1 + 0x44) = ((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) + 1) / 2;
  *(int *)(param_1 + 0x48) =
       ((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + 1) / 2;
  fVar2 = (float10)FUN_0044fb20((float)DAT_02ce99b0,
                                *(float *)(param_1 + 0x30) -
                                (float)*(int *)(param_1 + 0x44) / *(float *)(param_1 + 0x40));
  *(float *)(param_1 + 0x4c) = (float)fVar2;
  fVar2 = (float10)FUN_0044fb20((float)DAT_02ce99b4,
                                *(float *)(param_1 + 0x34) -
                                (float)*(int *)(param_1 + 0x48) / *(float *)(param_1 + 0x40));
  *(float *)(param_1 + 0x50) = (float)fVar2;
  fVar2 = (float10)FUN_00456080((float)DAT_02ce99b8,
                                (float)*(int *)(param_1 + 0x44) / *(float *)(param_1 + 0x40) +
                                *(float *)(param_1 + 0x30) + 5.0);
  *(float *)(param_1 + 0x54) = (float)fVar2;
  fVar2 = (float10)FUN_00456080((float)DAT_02ce99bc,
                                (float)*(int *)(param_1 + 0x48) / *(float *)(param_1 + 0x40) +
                                *(float *)(param_1 + 0x34) + 5.0);
  *(float *)(param_1 + 0x58) = (float)fVar2;
  *(int *)(param_1 + 0x5c) = (int)(*(float *)(param_1 + 0x4c) / 5.0);
  *(int *)(param_1 + 0x60) = (int)(*(float *)(param_1 + 0x50) / 5.0);
  *(int *)(param_1 + 100) = (int)(*(float *)(param_1 + 0x54) / 5.0);
  *(int *)(param_1 + 0x68) = (int)(*(float *)(param_1 + 0x58) / 5.0);
  return;
}

