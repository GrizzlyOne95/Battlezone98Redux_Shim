
void FUN_005c6230(int param_1)

{
  *(int *)(&DAT_009181c4 + param_1 * 8) = *(int *)(&DAT_009181c4 + param_1 * 8) + -1;
  if (*(int *)(&DAT_009181c0 + param_1 * 8) != 0) {
    (**(code **)(*(int *)(*(int *)(&DAT_009181c0 + param_1 * 8) + 0x18) + 0x10))();
  }
  return;
}

