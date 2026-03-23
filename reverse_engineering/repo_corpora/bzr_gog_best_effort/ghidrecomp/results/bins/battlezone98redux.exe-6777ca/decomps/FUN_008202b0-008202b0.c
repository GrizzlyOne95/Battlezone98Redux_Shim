
void FUN_008202b0(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = *param_3 * *param_2 + param_3[3] * param_2[1] + param_3[6] * param_2[2];
  fVar6 = param_3[1] * *param_2 + param_3[4] * param_2[1] + param_3[7] * param_2[2];
  fVar7 = param_3[2] * *param_2 + param_3[5] * param_2[1] + param_3[8] * param_2[2];
  fVar1 = param_2[3];
  dVar2 = *(double *)(param_3 + 10);
  dVar3 = *(double *)(param_3 + 0xc);
  dVar4 = *(double *)(param_3 + 0xe);
  *param_1 = fVar5;
  param_1[1] = fVar6;
  param_1[2] = fVar7;
  param_1[3] = (float)((((double)fVar1 - (double)fVar5 * dVar2) - (double)fVar6 * dVar3) -
                      (double)fVar7 * dVar4);
  FUN_0083e885();
  return;
}

