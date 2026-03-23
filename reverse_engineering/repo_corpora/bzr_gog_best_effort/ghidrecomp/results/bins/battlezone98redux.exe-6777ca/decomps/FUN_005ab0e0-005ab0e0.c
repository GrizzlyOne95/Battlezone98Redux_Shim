
float10 __thiscall FUN_005ab0e0(int *param_1,float param_2)

{
  float10 fVar1;
  float local_c;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_c = -1.0;
  fVar1 = (float10)(**(code **)(*param_1 + 0x1c))();
  if ((float)fVar1 == (float)param_1[0x1d]) {
    if (((*(uint *)(param_1[0x84] + 0x114) & 4) == 0) && ((float)param_1[0x41] <= 0.01)) {
      fVar1 = (float10)FUN_00453f80(param_1[0x45]);
      if ((float)fVar1 <= 0.01) {
        fVar1 = (float10)FUN_00453f80(param_1[0x46]);
        if ((float)fVar1 <= 0.01) {
          fVar1 = (float10)FUN_00453f80(param_1[0x47]);
          if ((float)fVar1 <= 0.01) goto LAB_005ab20e;
        }
      }
    }
    local_c = param_2 - (float)param_1[0x1b];
  }
  else {
    local_c = (param_2 - (float)param_1[0x1b]) + 1.0;
  }
LAB_005ab20e:
  fVar1 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar1 < 0.0) || ((*(uint *)(param_1[0x37] + 0x14) & 0x1000200) != 0)) {
    local_c = local_c + 10.0;
  }
  return (float10)local_c;
}

