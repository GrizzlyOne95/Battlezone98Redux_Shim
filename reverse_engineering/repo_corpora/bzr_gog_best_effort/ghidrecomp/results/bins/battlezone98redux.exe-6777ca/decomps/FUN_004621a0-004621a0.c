
void FUN_004621a0(float *param_1,float *param_2)

{
  float10 fVar1;
  double dVar2;
  float local_14;
  float local_10;
  float local_c;
  
  dVar2 = (double)(*param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2]);
  if (dVar2 <= 0.0) {
    local_c = 0.0;
    local_10 = 0.0;
    local_14 = 0.0;
  }
  else {
    fVar1 = (float10)FUN_00820570(dVar2);
    local_c = (float)fVar1;
    local_14 = *param_2 * local_c;
    local_10 = param_2[1] * local_c;
    local_c = param_2[2] * local_c;
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  FUN_0083e885();
  return;
}

