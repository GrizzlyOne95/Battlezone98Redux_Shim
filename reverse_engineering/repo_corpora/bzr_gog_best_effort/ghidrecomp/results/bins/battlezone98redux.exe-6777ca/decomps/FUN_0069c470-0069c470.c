
void FUN_0069c470(int *param_1)

{
  if (param_1 != (int *)0x0) {
    FUN_0069c470(param_1[3]);
    if (*param_1 != 0) {
      free((void *)*param_1);
    }
    if (param_1[2] != 0) {
      FUN_0069c420(param_1[2]);
    }
    free(param_1);
  }
  return;
}

