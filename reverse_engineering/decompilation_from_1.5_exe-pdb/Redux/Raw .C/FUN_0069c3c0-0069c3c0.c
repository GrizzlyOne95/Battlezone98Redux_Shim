
void FUN_0069c3c0(void *param_1)

{
  if (param_1 != (void *)0x0) {
    FUN_0069c3c0(*(undefined4 *)((int)param_1 + 0x24));
    if (*(int *)((int)param_1 + 4) != 0) {
      free(*(void **)((int)param_1 + 4));
    }
    if (*(int *)((int)param_1 + 8) != 0) {
      free(*(void **)((int)param_1 + 8));
    }
    free(param_1);
  }
  return;
}

