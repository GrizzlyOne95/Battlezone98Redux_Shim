
void FUN_00693330(int param_1,int param_2,int *param_3)

{
  int local_8;
  
  *(int **)(param_1 + param_2 * 4) = param_3;
  for (local_8 = 0; local_8 < *param_3; local_8 = local_8 + 1) {
    FUN_00693290(local_8 * 0x10 + param_3[1]);
  }
  return;
}

