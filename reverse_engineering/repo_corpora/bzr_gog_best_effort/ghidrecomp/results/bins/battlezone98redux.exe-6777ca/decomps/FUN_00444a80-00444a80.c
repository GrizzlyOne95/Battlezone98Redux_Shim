
void FUN_00444a80(float *param_1,float param_2,float param_3)

{
  *param_1 = param_2;
  if (0.0001 < param_2) {
    param_1[1] = 1.0 / param_2;
  }
  param_1[4] = param_3;
  if (param_3 <= 0.0001) {
    param_1[5] = 1e+10;
  }
  else {
    param_1[5] = param_2 / param_3;
  }
  return;
}

