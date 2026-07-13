
void FUN_005c8fc0(float *param_1,float *param_2,float param_3)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (float10)FUN_004178b0();
  fVar2 = (float)fVar1 * param_3 + *param_2;
  fVar1 = (float10)FUN_004178f0();
  fVar3 = (float)fVar1 * param_3 + param_2[2];
  fVar1 = (float10)FUN_007855e0((double)fVar2,(double)fVar3);
  *param_1 = fVar2;
  param_1[1] = (float)fVar1;
  param_1[2] = fVar3;
  FUN_0083e885();
  return;
}

