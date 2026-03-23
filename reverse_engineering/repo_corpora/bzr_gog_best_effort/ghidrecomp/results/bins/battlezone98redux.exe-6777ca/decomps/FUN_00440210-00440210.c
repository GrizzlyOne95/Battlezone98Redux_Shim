
void FUN_00440210(float *param_1,float *param_2,float *param_3)

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
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar1 = *param_2;
  fVar2 = param_3[1];
  fVar3 = param_2[1];
  fVar4 = param_3[4];
  fVar5 = param_2[2];
  fVar6 = param_3[7];
  fVar7 = *param_2;
  fVar8 = param_3[2];
  fVar9 = param_2[1];
  fVar10 = param_3[5];
  fVar11 = param_2[2];
  fVar12 = param_3[8];
  *param_1 = *param_2 * *param_3 + param_2[1] * param_3[3] + param_2[2] * param_3[6];
  param_1[1] = fVar1 * fVar2 + fVar3 * fVar4 + fVar5 * fVar6;
  param_1[2] = fVar7 * fVar8 + fVar9 * fVar10 + fVar11 * fVar12;
  FUN_0083e885();
  return;
}

