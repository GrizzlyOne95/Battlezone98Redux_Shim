
void FUN_00444540(int param_1)

{
  if (*(int *)(param_1 + 0x9c) != 0) {
    free(*(void **)(param_1 + 0x9c));
    *(undefined4 *)(param_1 + 0x9c) = 0;
  }
  return;
}

