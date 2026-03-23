
void FUN_0069c420(void *param_1)

{
  if (param_1 != (void *)0x0) {
    FUN_0069c420(*(undefined4 *)((int)param_1 + 0xc));
    if (*(int *)((int)param_1 + 4) != 0) {
      free(*(void **)((int)param_1 + 4));
    }
    free(param_1);
  }
  return;
}

