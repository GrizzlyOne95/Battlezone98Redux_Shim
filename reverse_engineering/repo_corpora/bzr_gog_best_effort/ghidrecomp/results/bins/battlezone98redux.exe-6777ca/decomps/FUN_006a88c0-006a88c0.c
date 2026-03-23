
void FUN_006a88c0(int *param_1)

{
  if (((param_1[8] == 0) && (*(int *)(*param_1 + 0x28) == 0)) && (*param_1 != 0)) {
    FUN_006a8900(*param_1);
  }
  free(param_1);
  return;
}

