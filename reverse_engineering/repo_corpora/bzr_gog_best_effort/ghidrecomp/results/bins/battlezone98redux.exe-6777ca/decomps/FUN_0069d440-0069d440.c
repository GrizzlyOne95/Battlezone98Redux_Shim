
void FUN_0069d440(undefined4 *param_1,void *param_2)

{
  *param_1 = 0xfffffc19;
  param_1[1] = 0;
  if (param_2 == (void *)param_1[3]) {
    if ((void *)param_1[4] == param_2) {
      param_1[4] = 0;
    }
    param_1[3] = *(undefined4 *)((int)param_2 + 4);
    if (param_1[3] != 0) {
      *(undefined4 *)(param_1[3] + 8) = 0;
    }
  }
  else if (param_2 == (void *)param_1[4]) {
    param_1[4] = *(undefined4 *)((int)param_2 + 8);
    if (param_1[4] != 0) {
      *(undefined4 *)(param_1[4] + 4) = 0;
    }
  }
  else if (param_2 != (void *)0x0) {
    if (*(int *)((int)param_2 + 8) != 0) {
      *(undefined4 *)(*(int *)((int)param_2 + 8) + 4) = *(undefined4 *)((int)param_2 + 4);
    }
    if (*(int *)((int)param_2 + 4) != 0) {
      *(undefined4 *)(*(int *)((int)param_2 + 4) + 8) = *(undefined4 *)((int)param_2 + 8);
    }
  }
  free(param_2);
  param_1[2] = param_1[2] + -1;
  return;
}

