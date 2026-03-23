
void FUN_00824a30(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  param_1[8] = param_2[8];
  *(double *)(param_1 + 10) = (double)(float)param_2[9];
  *(double *)(param_1 + 0xc) = (double)(float)param_2[10];
  *(double *)(param_1 + 0xe) = (double)(float)param_2[0xb];
  return;
}

