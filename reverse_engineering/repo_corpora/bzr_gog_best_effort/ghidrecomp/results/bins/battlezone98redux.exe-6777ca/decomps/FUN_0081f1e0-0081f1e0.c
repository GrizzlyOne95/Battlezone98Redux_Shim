
void FUN_0081f1e0(float *param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  uint local_24;
  float local_18 [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar4 = *param_2 + param_2[4] + param_2[8];
  if (fVar4 <= 0.0) {
    local_24 = (uint)(*param_2 <= param_2[4] && param_2[4] != *param_2);
    if (param_2[local_24 * 4] <= param_2[8] && param_2[8] != param_2[local_24 * 4]) {
      local_24 = 2;
    }
    iVar1 = *(int *)(&DAT_008fe1d4 + local_24 * 4);
    iVar2 = *(int *)(&DAT_008fe1d4 + iVar1 * 4);
    fVar3 = (float10)FUN_00417910(((param_2[local_24 * 4] + 1.0) - param_2[iVar1 * 4]) -
                                  param_2[iVar2 * 4]);
    local_18[local_24] = (float)fVar3 * 0.5;
    fVar4 = 0.5 / (float)fVar3;
    local_18[3] = (param_2[iVar2 * 3 + iVar1] - param_2[iVar1 * 3 + iVar2]) * fVar4;
    local_18[iVar1] = (param_2[iVar1 * 3 + local_24] + param_2[local_24 * 3 + iVar1]) * fVar4;
    local_18[iVar2] = (param_2[iVar2 * 3 + local_24] + param_2[local_24 * 3 + iVar2]) * fVar4;
  }
  else {
    fVar3 = (float10)FUN_00417910(fVar4 + 1.0);
    local_18[3] = (float)fVar3 * 0.5;
    local_18[2] = 0.5 / (float)fVar3;
    local_18[0] = (param_2[7] - param_2[5]) * local_18[2];
    local_18[1] = (param_2[2] - param_2[6]) * local_18[2];
    local_18[2] = (param_2[3] - param_2[1]) * local_18[2];
  }
  *param_1 = local_18[0];
  param_1[1] = local_18[1];
  param_1[2] = local_18[2];
  param_1[3] = local_18[3];
  FUN_0083e885();
  return;
}

