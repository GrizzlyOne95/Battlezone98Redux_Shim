
int FUN_0082ee9e(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x20);
  FUN_0082f0d6(param_1,1,0xffffffff);
  if (*(char *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 6) == '\0') {
    while (((*(byte *)(param_1 + 0x38) & 2) != 0 &&
           (iVar2 = *(int *)(*(int *)(param_1 + 0x14) + 0x14),
           *(int *)(*(int *)(param_1 + 0x14) + 0x14) = iVar2 + -1, iVar2 != 0))) {
      FUN_0082f0d6(param_1,4,0xffffffff);
    }
  }
  return *(int *)(param_1 + 0x20) + (param_2 - iVar1);
}

