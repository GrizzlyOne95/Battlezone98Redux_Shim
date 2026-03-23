
void FUN_0082d226(int param_1,int param_2)

{
  if (-1 < param_2) {
    while (*(uint *)(param_1 + 8) < (uint)(*(int *)(param_1 + 0xc) + param_2 * 0x10)) {
      *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 0xc) + param_2 * 0x10;
    return;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2 * 0x10 + 0x10;
  return;
}

