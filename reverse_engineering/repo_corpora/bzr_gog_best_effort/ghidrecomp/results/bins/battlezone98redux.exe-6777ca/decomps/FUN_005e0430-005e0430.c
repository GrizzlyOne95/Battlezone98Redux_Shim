
void __thiscall FUN_005e0430(int param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float local_28;
  float local_14;
  float local_10;
  float local_c;
  
  pfVar4 = (float *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
  local_14 = *pfVar4;
  local_10 = pfVar4[1];
  local_c = pfVar4[2];
  if ((*(int *)(param_1 + 0xcc) == 0) && (*(int *)(param_1 + 0xc4) != 0)) {
    fVar5 = (float10)FUN_004624d0();
    if (0.1 < (float)fVar5) {
      pfVar4 = (float *)FUN_004624b0();
      fVar1 = *pfVar4;
      fVar2 = pfVar4[1];
      fVar3 = pfVar4[2];
      fVar6 = *(float *)(*(int *)(param_1 + 0xc4) + 0x54);
      local_14 = local_14 - (float)*(double *)(param_1 + 0x50);
      local_10 = local_10 - (float)*(double *)(param_1 + 0x58);
      local_c = local_c - (float)*(double *)(param_1 + 0x60);
      fVar6 = (fVar1 * fVar1 + fVar2 * fVar2 + fVar3 * fVar3) - fVar6 * fVar6;
      local_28 = local_14 * fVar1 + local_10 * fVar2 + local_c * fVar3;
      fVar7 = local_28 * local_28 -
              fVar6 * (local_14 * local_14 + local_10 * local_10 + local_c * local_c);
      if (0.0 < fVar7) {
        fVar5 = (float10)FUN_00417910(fVar7);
        local_28 = -local_28 - (float)fVar5;
      }
      else {
        local_28 = -local_28;
      }
      local_28 = local_28 / fVar6;
      local_14 = (float)((double)local_14 + *(double *)(param_1 + 0x50) + (double)(local_28 * fVar1)
                        );
      local_10 = (float)((double)local_10 + *(double *)(param_1 + 0x58) + (double)(local_28 * fVar2)
                        );
      local_c = (float)((double)local_c + *(double *)(param_1 + 0x60) + (double)(local_28 * fVar3));
    }
  }
  *param_2 = local_14;
  param_2[1] = local_10;
  param_2[2] = local_c;
  FUN_0083e885();
  return;
}

