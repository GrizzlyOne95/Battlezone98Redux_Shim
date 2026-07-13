
int FUN_006895d0(int param_1,float *param_2,float param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  int local_18;
  uint local_14;
  
  fVar6 = *(float *)(param_1 + 0xf8) * param_2[2] + *(float *)(param_1 + 0xfc);
  uVar2 = (uint)(fVar6 + param_3) >> 0x1e & 2;
  uVar4 = (uint)(fVar6 - param_3) >> 0x1f;
  if ((uVar2 | uVar4) == 3) {
    iVar1 = 1;
  }
  else {
    fVar6 = *(float *)(param_1 + 0xe8) * param_2[2] + *(float *)(param_1 + 0xec);
    uVar3 = (uint)(fVar6 + param_3) >> 0x1e & 2;
    uVar5 = (uint)(fVar6 - param_3) >> 0x1f;
    if ((uVar3 | uVar5) == 3) {
      iVar1 = 1;
    }
    else {
      local_14 = uVar3 | uVar5 | uVar2 | uVar4;
      for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
        fVar6 = *(float *)(param_1 + 0xa0 + local_18 * 0x10) * *param_2 +
                *(float *)(param_1 + 0xa4 + local_18 * 0x10) * param_2[1] +
                *(float *)(param_1 + 0xa8 + local_18 * 0x10) * param_2[2];
        uVar2 = (uint)(fVar6 + param_3 * 1.1) >> 0x1e & 2;
        uVar4 = (uint)(fVar6 - param_3 * 1.1) >> 0x1f;
        if ((uVar2 | uVar4) == 3) {
          return 1;
        }
        local_14 = uVar2 | uVar4 | local_14;
      }
      iVar1 = -local_14;
    }
  }
  return iVar1;
}

