
void FUN_0062a650(float *param_1,float param_2,float *param_3,float *param_4)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float local_24;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  
  local_24 = *param_3 * *param_4 + param_3[1] * param_4[1] + param_3[2] * param_4[2] +
             param_3[3] * param_4[3];
  if (0.0 <= local_24) {
    fStack_18 = *param_3;
    fStack_14 = param_3[1];
    fStack_10 = param_3[2];
    fStack_c = param_3[3];
  }
  else {
    fStack_18 = -*param_3;
    fStack_14 = -param_3[1];
    fStack_10 = -param_3[2];
    fStack_c = -param_3[3];
    local_24 = -local_24;
  }
  if ((((1.0 - local_24 <= 1e-05) || (fStack_18 == 0.0)) || (fStack_18 == 1.0)) ||
     ((*param_4 == 0.0 || (*param_4 == 1.0)))) {
    fVar4 = 1.0 - param_2;
    param_1[1] = fVar4 * fStack_14 + param_2 * param_4[1];
    param_1[2] = fVar4 * fStack_10 + param_2 * param_4[2];
    param_1[3] = fVar4 * fStack_c + param_2 * param_4[3];
    *param_1 = fVar4 * fStack_18 + param_2 * *param_4;
    fVar1 = (float10)FUN_00417910(*param_1 * *param_1 + param_1[1] * param_1[1] +
                                  param_1[2] * param_1[2] + param_1[3] * param_1[3]);
    fVar4 = 1.0 / (float)fVar1;
    *param_1 = *param_1 * fVar4;
    param_1[1] = param_1[1] * fVar4;
    param_1[2] = param_1[2] * fVar4;
    param_1[3] = param_1[3] * fVar4;
  }
  else {
    fVar1 = (float10)FUN_004d9610(local_24);
    fVar4 = (float)fVar1;
    fVar1 = (float10)FUN_004178f0(fVar4);
    fVar2 = (float10)FUN_004178f0((1.0 - param_2) * fVar4);
    fVar3 = (float)fVar2 * (1.0 / (float)fVar1);
    fVar2 = (float10)FUN_004178f0(param_2 * fVar4);
    fVar4 = (float)fVar2 * (1.0 / (float)fVar1);
    param_1[1] = fVar3 * fStack_14 + fVar4 * param_4[1];
    param_1[2] = fVar3 * fStack_10 + fVar4 * param_4[2];
    param_1[3] = fVar3 * fStack_c + fVar4 * param_4[3];
    *param_1 = fVar3 * fStack_18 + fVar4 * *param_4;
  }
  FUN_0083e885();
  return;
}

