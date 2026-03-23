
void FUN_00445260(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar7 = (float)((double)*param_2 - *(double *)(param_3 + 10));
  fVar8 = (float)((double)param_2[1] - *(double *)(param_3 + 0xc));
  fVar9 = (float)((double)param_2[2] - *(double *)(param_3 + 0xe));
  fVar1 = param_3[3];
  fVar2 = param_3[4];
  fVar3 = param_3[5];
  fVar4 = param_3[6];
  fVar5 = param_3[7];
  fVar6 = param_3[8];
  *param_1 = fVar7 * *param_3 + fVar8 * param_3[1] + fVar9 * param_3[2];
  param_1[1] = fVar7 * fVar1 + fVar8 * fVar2 + fVar9 * fVar3;
  param_1[2] = fVar7 * fVar4 + fVar8 * fVar5 + fVar9 * fVar6;
  FUN_0083e885();
  return;
}

