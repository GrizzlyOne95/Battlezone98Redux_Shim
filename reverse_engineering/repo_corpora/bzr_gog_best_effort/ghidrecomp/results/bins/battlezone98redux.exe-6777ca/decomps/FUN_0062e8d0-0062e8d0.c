
float * FUN_0062e8d0(float *param_1,int param_2)

{
  double dVar1;
  float10 fVar2;
  
  if ((((*(double *)(param_2 + 0x160) - (double)DAT_008ec794 < 0.0) ||
       (0.0 < *(double *)(param_2 + 0x160) - (double)(DAT_008ec794 + 100.0))) ||
      (*(double *)(param_2 + 0x170) - (double)DAT_008ec79c < 0.0)) ||
     (0.0 < *(double *)(param_2 + 0x170) - (double)(DAT_008ec79c + 100.0))) {
    dVar1 = *(double *)(param_2 + 0x160);
    fVar2 = (float10)FUN_0062e800((float)*(double *)(param_2 + 0x160),0x42c80000);
    DAT_008ec794 = (float)dVar1 - (float)fVar2;
    dVar1 = *(double *)(param_2 + 0x170);
    fVar2 = (float10)FUN_0062e800((float)*(double *)(param_2 + 0x170),0x42c80000);
    DAT_008ec79c = (float)dVar1 - (float)fVar2;
  }
  *param_1 = DAT_008ec794;
  param_1[1] = DAT_008ec798;
  param_1[2] = DAT_008ec79c;
  return param_1;
}

