
int FUN_0082e1fd(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = (int *)(*(int *)(param_2 + 0x60) * 0x18 + *(int *)(param_1 + 0x28));
  iVar3 = FUN_0082db0e(param_1,piVar4,param_3);
  if (iVar3 != 0) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *piVar4;
    *(undefined4 *)(iVar2 + -0x10 + param_3 * 0x10) = *(undefined4 *)(iVar1 + -0x10);
    *(undefined4 *)(iVar2 + -0xc + param_3 * 0x10) = *(undefined4 *)(iVar1 + -0xc);
    *(undefined4 *)(iVar2 + -8 + param_3 * 0x10) = *(undefined4 *)(iVar1 + -8);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return iVar3;
}

