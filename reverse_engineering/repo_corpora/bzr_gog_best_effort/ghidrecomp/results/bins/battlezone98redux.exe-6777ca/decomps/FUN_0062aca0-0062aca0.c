
void FUN_0062aca0(float *param_1,float param_2,float *param_3,float *param_4)

{
  float fVar1;
  
  fVar1 = 1.0 - param_2;
  *param_1 = fVar1 * *param_3 + param_2 * *param_4;
  param_1[1] = fVar1 * param_3[1] + param_2 * param_4[1];
  param_1[2] = fVar1 * param_3[2] + param_2 * param_4[2];
  return;
}

