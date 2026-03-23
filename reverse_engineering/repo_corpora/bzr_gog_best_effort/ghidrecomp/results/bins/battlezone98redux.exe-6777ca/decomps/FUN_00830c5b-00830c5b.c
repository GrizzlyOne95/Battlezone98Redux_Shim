
int FUN_00830c5b(double *param_1)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 1) != 3) || (iVar1 = (int)ROUND(*param_1), (double)iVar1 != *param_1)) {
    iVar1 = -1;
  }
  return iVar1;
}

