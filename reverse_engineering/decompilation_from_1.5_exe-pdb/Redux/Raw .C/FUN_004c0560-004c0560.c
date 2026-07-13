
undefined4 FUN_004c0560(int param_1,float *param_2)

{
  undefined4 uVar1;
  int local_8;
  
  if ((int)(*(float *)(param_1 + 0xf8) * param_2[2] + *(float *)(param_1 + 0xfc)) < 0) {
    uVar1 = 0;
  }
  else if ((int)(*(float *)(param_1 + 0xe8) * param_2[2] + *(float *)(param_1 + 0xec)) < 0) {
    uVar1 = 0;
  }
  else {
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      if ((int)(*(float *)(param_1 + 0xa0 + local_8 * 0x10) * *param_2 +
                *(float *)(param_1 + 0xa4 + local_8 * 0x10) * param_2[1] +
                *(float *)(param_1 + 0xa8 + local_8 * 0x10) * param_2[2] + param_2[3]) < 0) {
        return 0;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

