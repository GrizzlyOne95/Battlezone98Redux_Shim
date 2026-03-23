
void FUN_008245a0(int *param_1,int *param_2)

{
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  if (param_2[1] == 0) {
    *param_1 = *param_2;
  }
  else {
    *(int *)param_2[1] = *param_2;
  }
  free(param_2);
  return;
}

