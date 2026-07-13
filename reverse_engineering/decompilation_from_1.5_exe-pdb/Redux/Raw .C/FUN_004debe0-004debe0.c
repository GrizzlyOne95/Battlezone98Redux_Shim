
void FUN_004debe0(float *param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  float local_34;
  float local_30;
  float local_2c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  
  local_30 = *param_2 * *param_3 + param_2[1] * param_3[1] + param_2[2] * param_3[2] +
             param_2[3] * param_3[3];
  if (0.0 <= local_30) {
    fStack_18 = *param_3;
    fStack_14 = param_3[1];
    fStack_10 = param_3[2];
    fStack_c = param_3[3];
  }
  else {
    local_30 = -local_30;
    fStack_18 = -*param_3;
    fStack_14 = -param_3[1];
    fStack_10 = -param_3[2];
    fStack_c = -param_3[3];
  }
  if (1.0 - local_30 <= 0.0001) {
    local_34 = 1.0 - param_4;
    local_2c = param_4;
  }
  else {
    fVar4 = (float10)FUN_004d9610(local_30);
    fVar3 = (float)fVar4;
    fVar4 = (float10)FUN_004178f0(fVar3);
    fVar5 = (float10)FUN_004178f0((1.0 - param_4) * fVar3);
    local_34 = (float)fVar5 / (float)fVar4;
    fVar5 = (float10)FUN_004178f0(param_4 * fVar3);
    local_2c = (float)fVar5 / (float)fVar4;
  }
  fVar3 = param_2[1];
  fVar1 = param_2[2];
  fVar2 = param_2[3];
  *param_1 = local_34 * *param_2 + local_2c * fStack_18;
  param_1[1] = local_34 * fVar3 + local_2c * fStack_14;
  param_1[2] = local_34 * fVar1 + local_2c * fStack_10;
  param_1[3] = local_34 * fVar2 + local_2c * fStack_c;
  FUN_0083e885();
  return;
}

