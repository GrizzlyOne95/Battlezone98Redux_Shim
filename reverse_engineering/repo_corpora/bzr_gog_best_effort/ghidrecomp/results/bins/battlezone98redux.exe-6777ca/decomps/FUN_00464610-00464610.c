
void FUN_00464610(int param_1,undefined4 param_2,undefined1 *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  uint local_c;
  int *local_8;
  
  iVar1 = FUN_00462380();
  iVar2 = FUN_00462380();
  local_8 = &DAT_0260d188;
  for (local_c = 0; local_c < 0x28; local_c = local_c + 1) {
    if ((*local_8 != 0) &&
       (fVar4 = (float10)FUN_00822d80(), 1.0 <= (float)fVar4 - (float)local_8[3])) {
      *local_8 = 0;
      local_8[1] = 0;
      local_8[2] = 0;
      local_8[3] = 0;
      local_8[4] = 0;
      local_8[5] = 0;
      local_8[6] = 0;
    }
    local_8 = local_8 + 7;
  }
  local_c = 0;
  for (local_8 = &DAT_0260d188;
      (local_c < 0x28 && (((*local_8 == 0 || (*local_8 != iVar1)) || (local_8[1] != iVar2))));
      local_8 = local_8 + 7) {
    local_c = local_c + 1;
  }
  if (local_c == 0x28) {
    local_c = 0;
    for (local_8 = &DAT_0260d188; (local_c < 0x28 && (*local_8 != 0)); local_8 = local_8 + 7) {
      local_c = local_c + 1;
    }
    if (local_c == 0x28) {
      return;
    }
    *local_8 = iVar1;
    local_8[1] = iVar2;
    local_8[2] = 0;
    fVar4 = (float10)FUN_00822d80();
    local_8[3] = (int)(float)fVar4;
    piVar3 = (int *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
    local_8[4] = *piVar3;
    local_8[5] = piVar3[1];
    local_8[6] = piVar3[2];
  }
  fVar4 = (float10)FUN_00822d80();
  local_8[2] = (int)(((float)fVar4 - (float)local_8[3]) + (float)local_8[2]);
  fVar4 = (float10)FUN_00822d80();
  local_8[3] = (int)(float)fVar4;
  if ((float)local_8[2] <= 10.0) {
    *param_3 = 0;
  }
  else {
    *param_3 = 1;
  }
  return;
}

