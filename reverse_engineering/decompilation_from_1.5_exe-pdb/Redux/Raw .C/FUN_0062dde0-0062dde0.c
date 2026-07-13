
void FUN_0062dde0(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0x7c) != 0) {
    FUN_0062dde0(*(undefined4 *)(param_1 + 0x7c),param_2);
  }
  if (*(int *)(param_1 + 0x80) != 0) {
    FUN_0062dde0(*(undefined4 *)(param_1 + 0x80),param_2);
  }
  *(uint *)(param_1 + 0x14) = ~param_2 & *(uint *)(param_1 + 0x14);
  return;
}

