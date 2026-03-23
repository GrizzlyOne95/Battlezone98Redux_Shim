
int FUN_0082e12e(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(*(int *)(param_2 + 0x60) * 0x18 + *(int *)(param_1 + 0x28));
  iVar1 = FUN_0082db0e(param_1,piVar2,param_3);
  if (iVar1 != 0) {
    FUN_0082c54d(param_1,*piVar2 + param_3 * 0x10 + -0x10);
  }
  return iVar1;
}

