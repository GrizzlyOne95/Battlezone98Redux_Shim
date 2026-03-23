
void FUN_00699650(int *param_1,int param_2)

{
  *(int *)(param_2 + 0x24) = param_1[1];
  param_1[1] = param_2;
  *param_1 = *param_1 + 1;
  return;
}

