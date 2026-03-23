
float10 __thiscall FUN_0047fb80(int *param_1,float param_2,float param_3)

{
  float fVar1;
  float10 fVar2;
  float local_c;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  fVar1 = (float)param_1[0x1b];
  fVar2 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar2 == (float)param_1[0x1d]) || (250.0 <= param_3)) {
    fVar2 = (float10)(**(code **)(*param_1 + 0x1c))();
    if (0.0 <= (float)fVar2) {
      local_c = -1.0;
    }
    else {
      local_c = (param_2 - fVar1) + 10.0;
    }
  }
  else {
    local_c = (param_2 - fVar1) + 5.0;
  }
  return (float10)local_c;
}

