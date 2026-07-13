
int FUN_0083032f(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = *(int *)(param_1 + 0x24);
  while (iVar1 != 0) {
    iVar1 = FUN_00830353(param_1);
    iVar2 = iVar2 + iVar1;
    iVar1 = *(int *)(param_1 + 0x24);
  }
  return iVar2;
}

