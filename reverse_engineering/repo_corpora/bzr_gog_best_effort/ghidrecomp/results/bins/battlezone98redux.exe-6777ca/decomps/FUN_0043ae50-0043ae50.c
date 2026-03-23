
undefined4 FUN_0043ae50(int param_1,int param_2,int param_3,int param_4)

{
  if (-1 < param_2) {
    *(int *)(param_1 + 0x40) = param_2;
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x80;
  }
  if (-1 < param_3) {
    *(float *)(param_1 + 0x20) = (float)param_3;
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x100;
  }
  if (-1 < param_4) {
    *(int *)(param_1 + 0x48) = param_4;
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x40;
  }
  return 1;
}

