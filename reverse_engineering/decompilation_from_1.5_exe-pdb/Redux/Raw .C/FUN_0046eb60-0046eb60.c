
void FUN_0046eb60(int param_1,double *param_2,double *param_3,double *param_4,double *param_5)

{
  double dVar1;
  undefined4 local_8;
  
  *param_3 = 1.0000000150474662e+30;
  *param_2 = 1.0000000150474662e+30;
  *param_5 = -1.0000000150474662e+30;
  *param_4 = -1.0000000150474662e+30;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 4); local_8 = local_8 + 1) {
    if ((double)*(float *)(*(int *)(param_1 + 8) + local_8 * 8) < *param_2) {
      *param_2 = (double)*(float *)(*(int *)(param_1 + 8) + local_8 * 8);
    }
    if ((double)*(float *)(*(int *)(param_1 + 8) + 4 + local_8 * 8) < *param_3) {
      *param_3 = (double)*(float *)(*(int *)(param_1 + 8) + 4 + local_8 * 8);
    }
    dVar1 = (double)*(float *)(*(int *)(param_1 + 8) + local_8 * 8);
    if (*param_4 <= dVar1 && dVar1 != *param_4) {
      *param_4 = (double)*(float *)(*(int *)(param_1 + 8) + local_8 * 8);
    }
    dVar1 = (double)*(float *)(*(int *)(param_1 + 8) + 4 + local_8 * 8);
    if (*param_5 <= dVar1 && dVar1 != *param_5) {
      *param_5 = (double)*(float *)(*(int *)(param_1 + 8) + 4 + local_8 * 8);
    }
  }
  return;
}

