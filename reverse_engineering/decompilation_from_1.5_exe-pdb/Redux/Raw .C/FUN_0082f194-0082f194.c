
void FUN_0082f194(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x2c);
  if (iVar1 < param_2) {
    iVar1 = iVar1 + param_2;
  }
  else {
    iVar1 = iVar1 * 2;
  }
  FUN_0082f596(param_1,iVar1);
  return;
}

