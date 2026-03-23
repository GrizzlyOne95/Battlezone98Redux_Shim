
float10 FUN_0062b4c0(int param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00822d60();
  if (*(int *)(param_1 + 0x10) < *(int *)(param_1 + 0x14)) {
    *(float *)(param_1 + 0xc) = (float)fVar1 * *(float *)(param_1 + 8) + *(float *)(param_1 + 0xc);
    if ((float)*(int *)(param_1 + 0x14) < *(float *)(param_1 + 0xc)) {
      if (*(int *)(param_1 + 0x1c) == 0) {
        *(float *)(param_1 + 0xc) = (float)*(int *)(param_1 + 0x14);
      }
      else {
        *(float *)(param_1 + 0xc) =
             (float)(*(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x14)) +
             *(float *)(param_1 + 0xc);
        if (0 < *(int *)(param_1 + 0x1c)) {
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
        }
      }
    }
    if (*(int *)(param_1 + 0x1c) != -1) {
      fVar1 = (float10)FUN_0043d610((float)*(int *)(param_1 + 0x14) - *(float *)(param_1 + 0xc));
      *(int *)(param_1 + 0x18) =
           (int)fVar1 +
           ((*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10)) + 1) * *(int *)(param_1 + 0x1c);
    }
  }
  else {
    *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) - (float)fVar1 * *(float *)(param_1 + 8);
    if (*(float *)(param_1 + 0xc) <= (float)*(int *)(param_1 + 0x14) &&
        (float)*(int *)(param_1 + 0x14) != *(float *)(param_1 + 0xc)) {
      if (*(int *)(param_1 + 0x1c) == 0) {
        *(float *)(param_1 + 0xc) = (float)*(int *)(param_1 + 0x14);
      }
      else {
        *(float *)(param_1 + 0xc) =
             (float)(*(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x14)) +
             *(float *)(param_1 + 0xc);
        if (0 < *(int *)(param_1 + 0x1c)) {
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
        }
      }
    }
    if (*(int *)(param_1 + 0x1c) != -1) {
      fVar1 = (float10)FUN_0043d610(*(float *)(param_1 + 0xc) - (float)*(int *)(param_1 + 0x14));
      *(int *)(param_1 + 0x18) =
           (int)fVar1 +
           ((*(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x14)) + 1) * *(int *)(param_1 + 0x1c);
    }
  }
  return (float10)*(float *)(param_1 + 0xc);
}

