
undefined4 FUN_00825a50(int param_1,int *param_2)

{
  if (*(int *)(*param_2 + 0x88) != 0) {
    *(undefined4 *)(*(int *)(*param_2 + 0x88) + 4) = *(undefined4 *)(param_1 + 0x34);
  }
  param_2[0xf] = *(int *)(param_1 + 0x20);
  param_2[0x10] = *(int *)(param_1 + 0x24);
  param_2[0x11] = *(int *)(param_1 + 0x28);
  param_2[0x12] = *(int *)(param_1 + 0x2c);
  param_2[0x13] = *(int *)(param_1 + 0x30);
  param_2[0x14] = 1;
  return 1;
}

