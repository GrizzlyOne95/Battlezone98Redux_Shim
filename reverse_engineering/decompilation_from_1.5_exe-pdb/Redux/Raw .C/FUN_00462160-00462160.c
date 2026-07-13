
void FUN_00462160(int param_1,float *param_2)

{
  *(double *)(param_1 + 0x28) = (double)*param_2;
  *(double *)(param_1 + 0x30) = (double)param_2[1];
  *(double *)(param_1 + 0x38) = (double)param_2[2];
  return;
}

