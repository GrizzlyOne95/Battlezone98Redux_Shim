
bool FUN_004461b0(float param_1,float param_2,float param_3,float param_4,float *param_5,
                 float *param_6)

{
  float local_c;
  float local_8;
  
  if ((param_2 <= -0.0001) || (0.0001 <= param_2)) {
    local_8 = (param_3 - param_1) / param_2;
    local_c = (param_4 - param_1) / param_2;
  }
  else {
    if ((param_1 < param_3) || (param_4 < param_1)) {
      return false;
    }
    local_8 = -1e+30;
    local_c = 1e+30;
  }
  if (local_8 <= local_c) {
    *param_5 = local_8;
    *param_6 = local_c;
  }
  else {
    *param_5 = local_c;
    *param_6 = local_8;
  }
  return 0.0 < *param_6 || *param_6 == 0.0;
}

