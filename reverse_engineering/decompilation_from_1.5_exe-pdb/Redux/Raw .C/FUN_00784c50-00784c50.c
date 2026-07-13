
void FUN_00784c50(int param_1,undefined4 param_2,double param_3)

{
  float in_stack_00000024;
  float *in_stack_00000030;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((double)param_1 <= param_3) {
    local_c = (float)param_1 + 0.9;
  }
  else {
    local_c = (float)param_1 + 0.1;
  }
  if (in_stack_00000024 == 0.0) {
    local_8 = 1e+30;
  }
  else {
    local_8 = (local_c - (float)param_3) / in_stack_00000024;
    if (local_8 < 0.0) {
      local_8 = 1e+30;
    }
  }
  if (local_8 < *in_stack_00000030) {
    *in_stack_00000030 = local_8;
  }
  return;
}

