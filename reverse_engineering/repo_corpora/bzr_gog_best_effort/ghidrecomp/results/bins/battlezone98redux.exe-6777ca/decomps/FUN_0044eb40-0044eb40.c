
void __thiscall FUN_0044eb40(int param_1,int param_2,int *param_3,int param_4)

{
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  param_3[3] = param_4;
  *param_3 = param_1;
  param_3[1] = param_2;
  param_3[2] = *(int *)(param_2 + 8);
  *(int **)(param_3[1] + 8) = param_3;
  *(int **)(param_3[2] + 4) = param_3;
  return;
}

