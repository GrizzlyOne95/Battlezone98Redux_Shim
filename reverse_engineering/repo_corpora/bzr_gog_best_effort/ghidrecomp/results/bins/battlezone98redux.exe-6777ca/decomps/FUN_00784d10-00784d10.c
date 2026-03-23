
void FUN_00784d10(undefined4 param_1,int param_2)

{
  double in_stack_0000001c;
  float in_stack_0000002c;
  float *in_stack_00000030;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((double)param_2 <= in_stack_0000001c) {
    local_c = (float)param_2 + 0.9;
  }
  else {
    local_c = (float)param_2 + 0.1;
  }
  if (in_stack_0000002c == 0.0) {
    local_8 = 1e+30;
  }
  else {
    local_8 = (local_c - (float)in_stack_0000001c) / in_stack_0000002c;
    if (local_8 < 0.0) {
      local_8 = 1e+30;
    }
  }
  if (local_8 < *in_stack_00000030) {
    *in_stack_00000030 = local_8;
  }
  return;
}

