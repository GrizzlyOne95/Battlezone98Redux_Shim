
void FUN_005872e0(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  if (param_4 < param_2) {
    local_18 = param_4;
    local_10 = param_2;
  }
  else {
    local_18 = param_2;
    local_10 = param_4;
  }
  if (param_5 < param_3) {
    local_14 = param_5;
    local_c = param_3;
  }
  else {
    local_14 = param_3;
    local_c = param_5;
  }
  *param_1 = local_18;
  param_1[1] = local_14;
  param_1[2] = local_10;
  param_1[3] = local_c;
  FUN_0083e885();
  return;
}

