
float10 __thiscall FUN_004ef920(int *param_1,float param_2,float param_3)

{
  int *piVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  int local_10;
  float local_8;
  
  if (param_2 < (float)param_1[0x1b]) {
    param_1[0x1b] = (int)param_2;
  }
  local_8 = param_2 - (float)param_1[0x1b];
  if ((float)param_1[0x7a] <= 0.0 && (float)param_1[0x7a] != 0.0) {
    local_8 = local_8 + 10.0;
  }
  local_8 = ((250.0 - param_3) / 250.0) * 5.0 + local_8;
  fVar3 = (float10)(**(code **)(*param_1 + 0x1c))();
  if (((float)fVar3 == (float)param_1[0x1d]) || (250.0 <= param_3)) {
    if ((param_1[0x39] == 0) &&
       (((float)param_1[0x41] <= 0.0001 && (float)param_1[0x41] != 0.0001 &&
        (local_8 = local_8 - 5.0, local_8 < 0.0)))) {
      local_8 = 0.0;
    }
  }
  else {
    local_8 = local_8 + 1.0;
  }
  piVar1 = (int *)FUN_00417c70();
  if (param_1 + -6 == piVar1) {
    local_8 = local_8 + 0.2;
  }
  if (param_1[0x62] != 0) {
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      iVar2 = FUN_00417f60(local_10);
      if ((iVar2 != 0) && ((float)param_1[0x1b] <= *(float *)(iVar2 + 0xac))) {
        local_8 = local_8 + 1.0;
        break;
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

