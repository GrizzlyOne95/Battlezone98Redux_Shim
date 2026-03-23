
void FUN_006886a0(float *param_1,int param_2,int param_3,int param_4,int param_5)

{
  float fVar1;
  
  *param_1 = (float)(param_2 + param_4) * 0.5;
  param_1[1] = (float)(param_3 + param_5) * 0.5;
  fVar1 = (float)(param_5 - param_3) * 0.5 * param_1[0xc];
  param_1[2] = fVar1 / (param_1[0xb] * param_1[10]);
  param_1[3] = -fVar1 / param_1[10];
  FUN_00688760(param_1,param_2,param_3,param_4,param_5);
  return;
}

