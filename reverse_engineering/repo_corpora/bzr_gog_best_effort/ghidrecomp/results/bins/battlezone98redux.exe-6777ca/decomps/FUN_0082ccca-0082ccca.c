
void FUN_0082ccca(int param_1,int param_2)

{
  double *pdVar1;
  
  pdVar1 = *(double **)(param_1 + 8);
  *(undefined4 *)(pdVar1 + 1) = 3;
  *pdVar1 = (double)param_2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

