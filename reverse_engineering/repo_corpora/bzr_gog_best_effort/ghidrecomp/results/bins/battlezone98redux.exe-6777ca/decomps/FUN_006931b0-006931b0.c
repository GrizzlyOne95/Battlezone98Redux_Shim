
void FUN_006931b0(int *param_1)

{
  int local_8;
  
  if (param_1[1] != 0) {
    for (local_8 = 0; local_8 < *param_1; local_8 = local_8 + 1) {
      if (*(int *)(param_1[1] + 0xc + local_8 * 0x10) != 0) {
        free(*(void **)(param_1[1] + 0xc + local_8 * 0x10));
      }
    }
    free((void *)param_1[1]);
  }
  free(param_1);
  return;
}

