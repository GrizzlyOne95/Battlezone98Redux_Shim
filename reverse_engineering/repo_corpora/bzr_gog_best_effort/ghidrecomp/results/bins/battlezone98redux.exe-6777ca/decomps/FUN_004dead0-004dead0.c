
void FUN_004dead0(float *param_1)

{
  float10 fVar1;
  float fVar2;
  float local_8;
  
  local_8 = *param_1 * *param_1 + param_1[1] * param_1[1] + param_1[2] * param_1[2] +
            param_1[3] * param_1[3];
  fVar1 = (float10)FUN_00453f80(local_8);
  if ((float)fVar1 < 0.0001) {
    local_8 = 0.0001;
  }
  fVar1 = (float10)FUN_00417910(local_8);
  fVar2 = 1.0 / (float)fVar1;
  *param_1 = *param_1 * fVar2;
  param_1[1] = param_1[1] * fVar2;
  param_1[2] = param_1[2] * fVar2;
  param_1[3] = param_1[3] * fVar2;
  return;
}

