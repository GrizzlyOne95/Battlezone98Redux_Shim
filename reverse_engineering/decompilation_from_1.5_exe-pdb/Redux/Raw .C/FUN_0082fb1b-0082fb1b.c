
int FUN_0082fb1b(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar1 = *(int *)(param_1 + 0x18);
    iVar3 = 0;
    do {
      if (param_3 < *(int *)(iVar3 + 4 + iVar1)) {
        return 0;
      }
      if ((param_3 < *(int *)(iVar3 + 8 + iVar1)) && (param_2 = param_2 + -1, param_2 == 0)) {
        return *(int *)(iVar2 * 0xc + iVar1) + 0x10;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0xc;
    } while (iVar2 < *(int *)(param_1 + 0x38));
  }
  return 0;
}

