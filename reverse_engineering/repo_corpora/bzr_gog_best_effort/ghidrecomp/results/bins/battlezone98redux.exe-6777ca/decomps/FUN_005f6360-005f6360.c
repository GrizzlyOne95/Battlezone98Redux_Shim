
float10 __thiscall FUN_005f6360(int *param_1,float param_2,float param_3)

{
  char cVar1;
  int *piVar2;
  float10 fVar3;
  float fVar4;
  int local_10;
  float local_8;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_8 = param_2 - (float)param_1[0x1b];
  fVar3 = (float10)(**(code **)(*param_1 + 0x1c))();
  if ((float)fVar3 != (float)param_1[0x1d]) {
    local_8 = local_8 + 1.0;
  }
  local_8 = ((250.0 - param_3) / 250.0) * 5.0 + local_8;
  if (0.0 < (float)param_1[0x7a]) {
    if (((param_1[0x84] == 2) && (250.0 <= param_3)) && (local_8 = local_8 - 5.0, local_8 < 0.0)) {
      local_8 = 0.0;
    }
  }
  else {
    local_8 = local_8 + 10.0;
  }
  piVar2 = (int *)FUN_00417c70();
  if (param_1 + -6 == piVar2) {
    local_8 = local_8 + 0.2;
  }
  if (param_1[0x62] != 0) {
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      piVar2 = (int *)FUN_00417f60(local_10);
      if (piVar2 != (int *)0x0) {
        cVar1 = (**(code **)(*piVar2 + 0x10))();
        if (cVar1 != '\0') {
          local_8 = local_8 + 0.1;
          break;
        }
      }
    }
  }
  fVar4 = (float)param_1[0xb1] - *(float *)(param_1[0x86] + 0xcc);
  if ((0.1 < fVar4) || (fVar4 < -0.1)) {
    local_8 = local_8 + 0.1;
  }
  fVar4 = (float)param_1[0xb2] - *(float *)(param_1[0x86] + 0xc4);
  if ((0.1 < fVar4) || (fVar4 < -0.1)) {
    local_8 = local_8 + 0.1;
  }
  fVar4 = (float)param_1[0xb3] - *(float *)(param_1[0x86] + 200);
  if ((0.1 < fVar4) || (fVar4 < -0.1)) {
    local_8 = local_8 + 0.1;
  }
  fVar4 = (float)param_1[0xb4] - *(float *)(param_1[0x86] + 0xd0);
  if ((0.1 < fVar4) || (fVar4 < -0.1)) {
    local_8 = local_8 + 0.1;
  }
  if (param_1[0xb6] != *(int *)(param_1[0x86] + 0xd8)) {
    local_8 = local_8 + 0.1;
  }
  if (param_1[0xb7] != *(int *)(param_1[0x86] + 0xd4)) {
    local_8 = local_8 + 0.1;
  }
  if (param_1[0xb8] != *(int *)(param_1[0x86] + 0xdc)) {
    local_8 = local_8 + 0.1;
  }
  return (float10)local_8;
}

