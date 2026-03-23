
void FUN_0081f530(float *param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  float fVar7;
  float local_24;
  float local_20;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  fVar7 = *param_2 * *param_3 + param_2[1] * param_3[1] + param_2[2] * param_3[2] +
          param_2[3] * param_3[3];
  if (fVar7 + 1.0 <= 0.0001) {
    fVar7 = param_2[1];
    fVar3 = *param_2;
    fVar1 = param_2[3];
    fVar2 = param_2[2];
    fVar4 = (float)FUN_008205a0((1.0 - param_4) * 3.1415927 * 0.5);
    fVar5 = (float)FUN_008205a0(param_4 * 3.1415927 * 0.5);
    local_c = param_2[3] * fVar4 + fVar2 * fVar5;
    local_18 = *param_2 * fVar4 + -fVar7 * fVar5;
    local_14 = param_2[1] * fVar4 + fVar3 * fVar5;
    local_10 = param_2[2] * fVar4 + fVar1 * fVar5;
  }
  else {
    if (1.0 - fVar7 <= 0.0001) {
      local_24 = 1.0 - param_4;
      local_20 = param_4;
    }
    else {
      fVar6 = (float10)FUN_0081eaf0(fVar7);
      fVar7 = (float)fVar6;
      fVar3 = (float)FUN_008205a0(fVar7);
      local_24 = (float)FUN_008205a0((1.0 - param_4) * fVar7);
      local_20 = (float)FUN_008205a0(param_4 * fVar7);
      local_24 = local_24 * (1.0 / fVar3);
      local_20 = local_20 * (1.0 / fVar3);
    }
    local_c = param_2[3] * local_24 + param_3[3] * local_20;
    local_18 = *param_2 * local_24 + *param_3 * local_20;
    local_14 = param_2[1] * local_24 + param_3[1] * local_20;
    local_10 = param_2[2] * local_24 + param_3[2] * local_20;
  }
  fVar7 = local_18 * local_18 + local_14 * local_14 + local_10 * local_10 + local_c * local_c;
  if (0.0001 < 1.0 - fVar7) {
    fVar6 = (float10)FUN_00417910(fVar7);
    fVar7 = (float)(0.9999 / (double)fVar6);
    local_18 = local_18 * fVar7;
    local_14 = local_14 * fVar7;
    local_10 = local_10 * fVar7;
    local_c = local_c * fVar7;
  }
  *param_1 = local_18;
  param_1[1] = local_14;
  param_1[2] = local_10;
  param_1[3] = local_c;
  FUN_0083e885();
  return;
}

