
bool FUN_0082cdaf(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 8);
  *piVar1 = param_1;
  piVar1[2] = 8;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return *(int *)(*(int *)(param_1 + 0x10) + 0x70) == param_1;
}

