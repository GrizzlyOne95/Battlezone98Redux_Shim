
void FUN_0081fe60(float *param_1,float *param_2,float *param_3)

{
  int iVar1;
  float *pfVar2;
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_48[0] = *param_2 * *param_3 + param_2[1] * param_3[3] + param_2[2] * param_3[6];
  local_48[1] = *param_2 * param_3[1] + param_2[1] * param_3[4] + param_2[2] * param_3[7];
  local_48[2] = *param_2 * param_3[2] + param_2[1] * param_3[5] + param_2[2] * param_3[8];
  local_48[3] = param_2[3] * *param_3 + param_2[4] * param_3[3] + param_2[5] * param_3[6];
  local_38 = param_2[3] * param_3[1] + param_2[4] * param_3[4] + param_2[5] * param_3[7];
  local_34 = param_2[3] * param_3[2] + param_2[4] * param_3[5] + param_2[5] * param_3[8];
  local_30 = param_2[6] * *param_3 + param_2[7] * param_3[3] + param_2[8] * param_3[6];
  local_2c = param_2[6] * param_3[1] + param_2[7] * param_3[4] + param_2[8] * param_3[7];
  local_28 = param_2[6] * param_3[2] + param_2[7] * param_3[5] + param_2[8] * param_3[8];
  local_20 = (double)*param_3 * *(double *)(param_2 + 10) +
             (double)param_3[3] * *(double *)(param_2 + 0xc) +
             (double)param_3[6] * *(double *)(param_2 + 0xe) + *(double *)(param_3 + 10);
  local_18 = (double)param_3[1] * *(double *)(param_2 + 10) +
             (double)param_3[4] * *(double *)(param_2 + 0xc) +
             (double)param_3[7] * *(double *)(param_2 + 0xe) + *(double *)(param_3 + 0xc);
  local_10 = (double)param_3[2] * *(double *)(param_2 + 10) +
             (double)param_3[5] * *(double *)(param_2 + 0xc) +
             (double)param_3[8] * *(double *)(param_2 + 0xe) + *(double *)(param_3 + 0xe);
  pfVar2 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

