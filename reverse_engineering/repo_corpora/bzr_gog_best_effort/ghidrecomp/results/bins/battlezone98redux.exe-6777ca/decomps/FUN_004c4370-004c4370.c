
void __fastcall FUN_004c4370(int param_1)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0xfc);
  *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(param_1 + 0xec);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0xf0);
  if (*(int *)(param_1 + 0xec) == 0) {
    local_1c = 0.0;
  }
  else {
    local_1c = 6.0 / (float)*(int *)(param_1 + 0xec);
  }
  if (*(int *)(param_1 + 0xf0) == 0) {
    local_20 = 0.0;
  }
  else {
    local_20 = 6.0 / (float)*(int *)(param_1 + 0xf0);
  }
  fVar1 = *(float *)(param_1 + 0x144);
  fVar2 = *(float *)(param_1 + 0x144);
  local_10 = -local_20 * 0.5 * (float)*(int *)(param_1 + 0xf0);
  for (local_14 = 0; local_14 <= *(int *)(param_1 + 0xf0); local_14 = local_14 + 1) {
    local_c = -local_1c * 0.5 * (float)*(int *)(param_1 + 0xec);
    for (local_18 = 0; local_18 <= *(int *)(param_1 + 0xec); local_18 = local_18 + 1) {
      fVar3 = (float10)FUN_0045c400((local_c * local_c + local_10 * local_10) *
                                    (-1.0 / (fVar1 * 2.0 * fVar2)));
      *(float *)(param_1 + 0x148 + local_14 * 0x100 + local_18 * 4) = (float)fVar3;
      local_c = local_c + local_1c;
    }
    local_10 = local_10 + local_20;
  }
  return;
}

