
void FUN_0049f880(int param_1)

{
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
      FUN_0049f880(local_8 * 0x20 + *(int *)(param_1 + 0x18));
    }
    free(*(void **)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}

