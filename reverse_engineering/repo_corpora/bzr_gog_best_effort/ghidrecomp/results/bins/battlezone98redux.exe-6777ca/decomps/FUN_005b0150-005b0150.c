
float10 __thiscall FUN_005b0150(int *param_1,float param_2,float param_3)

{
  float10 fVar1;
  float local_8;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_8 = ((250.0 - param_3) / 250.0) * 5.0 + (param_2 - (float)param_1[0x1b]);
  fVar1 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar1 != (float)param_1[0x1d]) && (param_3 < 250.0)) {
    local_8 = local_8 + 1.0;
  }
  if (0.0 < (float)param_1[0x7a]) {
    if ((param_1[0x84] == 2) && (local_8 = local_8 - 5.0, local_8 < 0.0)) {
      local_8 = 0.0;
    }
  }
  else {
    local_8 = local_8 + 10.0;
  }
  return (float10)local_8;
}

