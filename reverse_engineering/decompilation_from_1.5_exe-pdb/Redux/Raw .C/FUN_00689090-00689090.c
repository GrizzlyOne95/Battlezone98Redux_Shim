
void FUN_00689090(int param_1,float *param_2)

{
  double *pdVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_a0 [64];
  double local_60;
  double local_58;
  double local_50;
  double local_48;
  double local_40;
  double local_38;
  double local_30;
  double local_28;
  double local_20;
  double local_18;
  double local_10;
  int local_8;
  
  *(undefined8 *)(param_1 + 0x160) = *(undefined8 *)(param_2 + 10);
  *(undefined8 *)(param_1 + 0x168) = *(undefined8 *)(param_2 + 0xc);
  *(undefined8 *)(param_1 + 0x170) = *(undefined8 *)(param_2 + 0xe);
  local_30 = *(double *)(param_1 + 0x160);
  local_20 = *(double *)(param_1 + 0x160);
  local_40 = *(double *)(param_1 + 0x168);
  local_38 = *(double *)(param_1 + 0x168);
  local_28 = *(double *)(param_1 + 0x170);
  local_10 = *(double *)(param_1 + 0x170);
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    *(double *)(param_1 + 0x160 + (local_8 + 1) * 0x18) =
         (double)(*param_2 * *(float *)(param_1 + 0x100 + (local_8 + 4) * 0xc) +
                  param_2[3] * *(float *)(param_1 + 0x104 + (local_8 + 4) * 0xc) +
                 param_2[6] * *(float *)(param_1 + 0x108 + (local_8 + 4) * 0xc)) +
         *(double *)(param_2 + 10);
    *(double *)(param_1 + 0x168 + (local_8 + 1) * 0x18) =
         (double)(param_2[1] * *(float *)(param_1 + 0x100 + (local_8 + 4) * 0xc) +
                  param_2[4] * *(float *)(param_1 + 0x104 + (local_8 + 4) * 0xc) +
                 param_2[7] * *(float *)(param_1 + 0x108 + (local_8 + 4) * 0xc)) +
         *(double *)(param_2 + 0xc);
    *(double *)(param_1 + 0x170 + (local_8 + 1) * 0x18) =
         (double)(param_2[2] * *(float *)(param_1 + 0x100 + (local_8 + 4) * 0xc) +
                  param_2[5] * *(float *)(param_1 + 0x104 + (local_8 + 4) * 0xc) +
                 param_2[8] * *(float *)(param_1 + 0x108 + (local_8 + 4) * 0xc)) +
         *(double *)(param_2 + 0xe);
    pdVar1 = (double *)(param_1 + 0x160 + (local_8 + 1) * 0x18);
    if (*pdVar1 <= local_30 && local_30 != *pdVar1) {
      local_30 = *(double *)(param_1 + 0x160 + (local_8 + 1) * 0x18);
    }
    pdVar1 = (double *)(param_1 + 0x168 + (local_8 + 1) * 0x18);
    if (*pdVar1 <= local_40 && local_40 != *pdVar1) {
      local_40 = *(double *)(param_1 + 0x168 + (local_8 + 1) * 0x18);
    }
    pdVar1 = (double *)(param_1 + 0x170 + (local_8 + 1) * 0x18);
    if (*pdVar1 <= local_28 && local_28 != *pdVar1) {
      local_28 = *(double *)(param_1 + 0x170 + (local_8 + 1) * 0x18);
    }
    if (local_20 < *(double *)(param_1 + 0x160 + (local_8 + 1) * 0x18)) {
      local_20 = *(double *)(param_1 + 0x160 + (local_8 + 1) * 0x18);
    }
    if (local_38 < *(double *)(param_1 + 0x168 + (local_8 + 1) * 0x18)) {
      local_38 = *(double *)(param_1 + 0x168 + (local_8 + 1) * 0x18);
    }
    if (local_10 < *(double *)(param_1 + 0x170 + (local_8 + 1) * 0x18)) {
      local_10 = *(double *)(param_1 + 0x170 + (local_8 + 1) * 0x18);
    }
  }
  *(double *)(param_1 + 0x80) = (local_30 + local_20) * 0.5;
  *(double *)(param_1 + 0x88) = (local_40 + local_38) * 0.5;
  *(double *)(param_1 + 0x90) = (local_28 + local_10) * 0.5;
  local_18 = 0.0;
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    local_48 = *(double *)(param_1 + 0x80) - *(double *)(param_1 + 0x160 + local_8 * 0x18);
    local_60 = *(double *)(param_1 + 0x88) - *(double *)(param_1 + 0x168 + local_8 * 0x18);
    local_50 = *(double *)(param_1 + 0x90) - *(double *)(param_1 + 0x170 + local_8 * 0x18);
    local_58 = local_48 * local_48 + local_60 * local_60 + local_50 * local_50;
    if (local_18 < local_58) {
      local_18 = local_58;
    }
  }
  *(double *)(param_1 + 0x98) = SQRT(local_18);
  puVar2 = (undefined4 *)FUN_008203f0(local_a0,param_2);
  puVar4 = (undefined4 *)(param_1 + 0x40);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  return;
}

