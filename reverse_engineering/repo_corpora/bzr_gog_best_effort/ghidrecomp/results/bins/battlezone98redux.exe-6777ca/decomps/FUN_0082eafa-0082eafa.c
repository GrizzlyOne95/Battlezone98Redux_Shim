
bool FUN_0082eafa(double *param_1,double *param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)(param_1 + 1);
  if (iVar1 == *(int *)(param_2 + 1)) {
    if (iVar1 == 0) {
      bVar2 = true;
    }
    else if (((iVar1 == 1) || (iVar1 == 2)) || (iVar1 != 3)) {
      bVar2 = *(int *)param_1 == *(int *)param_2;
    }
    else {
      bVar2 = *param_1 == *param_2;
    }
    return bVar2;
  }
  return false;
}

