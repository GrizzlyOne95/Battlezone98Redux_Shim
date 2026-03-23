
float10 __thiscall FUN_005f1cc0(int *param_1,float param_2,float param_3)

{
  float10 fVar1;
  float local_c;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_c = ((250.0 - param_3) / 250.0) * 5.0 + (param_2 - (float)param_1[0x1b]);
  fVar1 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar1 != (float)param_1[0x1d]) && (param_3 < 250.0)) {
    local_c = local_c + 1.0;
  }
  if ((float)param_1[0x7a] <= 0.0) {
    local_c = local_c + 10.0;
  }
  return (float10)local_c;
}

