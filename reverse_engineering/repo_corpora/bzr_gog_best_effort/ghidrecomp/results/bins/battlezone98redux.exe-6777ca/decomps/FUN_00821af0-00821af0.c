
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00821af0(float param_1,int param_2,int param_3)

{
  float10 fVar1;
  
  DAT_00946744 = param_2;
  DAT_00946778 = (double)(*(float *)(*(int *)(param_3 + 8) + 8 + param_2 * 8) -
                         *(float *)(*(int *)(param_3 + 8) + param_2 * 8));
  DAT_00946780 = (double)(*(float *)(*(int *)(param_3 + 8) + 0xc + param_2 * 8) -
                         *(float *)(*(int *)(param_3 + 8) + 4 + param_2 * 8));
  DAT_00946748 = (double)param_1;
  DAT_00946768 = (double)*(float *)(*(int *)(param_3 + 8) + param_2 * 8) +
                 (double)param_1 * DAT_00946778;
  DAT_00946770 = (double)*(float *)(*(int *)(param_3 + 8) + 4 + param_2 * 8) +
                 (double)param_1 * DAT_00946780;
  if ((0.0001 < DAT_00946778 * DAT_00946778 + DAT_00946780 * DAT_00946780) ||
     (DAT_00946778 * DAT_00946778 + DAT_00946780 * DAT_00946780 < -0.0001)) {
    fVar1 = (float10)FUN_00820570(DAT_00946778 * DAT_00946778 + DAT_00946780 * DAT_00946780);
    _DAT_00946750 = (double)fVar1;
  }
  else {
    _DAT_00946750 = 0.0;
  }
  return;
}

