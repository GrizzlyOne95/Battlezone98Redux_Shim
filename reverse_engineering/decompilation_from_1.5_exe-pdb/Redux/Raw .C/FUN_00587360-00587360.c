
int FUN_00587360(int *param_1)

{
  int local_c;
  
  local_c = (param_1[2] - *param_1) * (param_1[3] - param_1[1]);
  if (local_c < 0) {
    local_c = -local_c;
  }
  return local_c;
}

