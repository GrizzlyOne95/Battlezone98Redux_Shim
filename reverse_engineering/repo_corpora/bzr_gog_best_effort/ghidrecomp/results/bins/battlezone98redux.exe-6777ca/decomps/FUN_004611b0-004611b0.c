
uint __thiscall FUN_004611b0(uint param_1,undefined4 *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined8 uVar6;
  float local_3c;
  float local_38;
  float local_14;
  bool local_8;
  bool local_5;
  
  if (*(int *)(param_1 + 4) < 3) {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    uVar6 = FUN_0045c460(*param_2,param_2[1],param_2[2]);
    fVar5 = (float)((ulonglong)uVar6 >> 0x20);
    fVar3 = (float)uVar6;
    fVar4 = *(float *)(*(int *)(param_1 + 8) + -8 + *(int *)(param_1 + 4) * 8);
    local_38 = *(float *)(*(int *)(param_1 + 8) + -4 + *(int *)(param_1 + 4) * 8);
    local_5 = false;
    local_14 = 0.0;
    local_3c = fVar4;
    local_8 = fVar5 <= local_38;
    while ((int)local_14 < *(int *)(param_1 + 4)) {
      fVar1 = *(float *)(*(int *)(param_1 + 8) + (int)local_14 * 8);
      fVar2 = *(float *)(*(int *)(param_1 + 8) + 4 + (int)local_14 * 8);
      if (local_8 != fVar5 <= fVar2) {
        if (fVar3 <= local_3c == fVar3 <= fVar1) {
          if (fVar3 <= local_3c) {
            local_5 = local_5 == false;
          }
        }
        else if (fVar3 <= fVar1 - ((fVar2 - fVar5) * (local_3c - fVar1)) / (local_38 - fVar2)) {
          local_5 = local_5 == false;
        }
      }
      fVar4 = (float)((int)local_14 + 1);
      local_3c = fVar1;
      local_38 = fVar2;
      local_8 = fVar5 <= fVar2;
      local_14 = fVar4;
    }
    param_1 = CONCAT31((int3)((uint)fVar4 >> 8),local_5);
  }
  return param_1;
}

