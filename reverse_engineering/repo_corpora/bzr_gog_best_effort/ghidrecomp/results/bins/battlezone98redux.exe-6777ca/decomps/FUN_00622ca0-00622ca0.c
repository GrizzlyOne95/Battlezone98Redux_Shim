
undefined4 FUN_00622ca0(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x60) != 0) {
      free(*(void **)(param_1 + 0x60));
    }
    if (*(int *)(param_1 + 100) != 0) {
      free(*(void **)(param_1 + 100));
    }
    if (*(int *)(param_1 + 0x68) != 0) {
      free(*(void **)(param_1 + 0x68));
    }
    if (*(int *)(param_1 + 0x6c) != 0) {
      free(*(void **)(param_1 + 0x6c));
    }
    if (*(int *)(param_1 + 0x70) != 0) {
      free(*(void **)(param_1 + 0x70));
    }
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = 0;
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  return 0;
}

