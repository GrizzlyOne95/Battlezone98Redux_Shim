
void FUN_008203f0(float *param_1,float *param_2)

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
  local_48[0] = *param_2;
  local_48[1] = param_2[3];
  local_48[2] = param_2[6];
  local_48[3] = param_2[1];
  local_38 = param_2[4];
  local_34 = param_2[7];
  local_30 = param_2[2];
  local_2c = param_2[5];
  local_28 = param_2[8];
  local_20 = -((double)*param_2 * *(double *)(param_2 + 10) +
               (double)param_2[1] * *(double *)(param_2 + 0xc) +
              (double)param_2[2] * *(double *)(param_2 + 0xe));
  local_18 = -((double)param_2[3] * *(double *)(param_2 + 10) +
               (double)param_2[4] * *(double *)(param_2 + 0xc) +
              (double)param_2[5] * *(double *)(param_2 + 0xe));
  local_10 = -((double)param_2[6] * *(double *)(param_2 + 10) +
               (double)param_2[7] * *(double *)(param_2 + 0xc) +
              (double)param_2[8] * *(double *)(param_2 + 0xe));
  pfVar2 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

