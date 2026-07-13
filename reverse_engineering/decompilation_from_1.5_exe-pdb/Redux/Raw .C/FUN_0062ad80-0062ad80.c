
void FUN_0062ad80(float *param_1,float *param_2)

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
  
  fVar1 = param_2[1] * 2.0 * param_2[1];
  fVar2 = param_2[1] * 2.0 * param_2[2];
  fVar3 = param_2[1] * 2.0 * param_2[3];
  fVar4 = param_2[2] * 2.0 * param_2[2];
  fVar5 = param_2[2] * 2.0 * param_2[3];
  fVar6 = param_2[3] * 2.0 * param_2[3];
  fVar7 = *param_2 * 2.0 * param_2[1];
  fVar8 = *param_2 * 2.0 * param_2[2];
  fVar9 = *param_2 * 2.0 * param_2[3];
  *param_1 = 1.0 - (fVar4 + fVar6);
  param_1[1] = fVar2 - fVar9;
  param_1[2] = fVar3 + fVar8;
  param_1[3] = fVar2 + fVar9;
  param_1[4] = 1.0 - (fVar1 + fVar6);
  param_1[5] = fVar5 - fVar7;
  param_1[6] = fVar3 - fVar8;
  param_1[7] = fVar5 + fVar7;
  param_1[8] = 1.0 - (fVar1 + fVar4);
  return;
}

