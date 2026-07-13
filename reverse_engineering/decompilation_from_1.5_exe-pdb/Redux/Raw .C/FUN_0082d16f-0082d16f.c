
undefined4 FUN_0082d16f(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar3 = 0;
  if (*(int *)(*(int *)(param_1 + 8) + -8) != 0) {
    iVar3 = *(int *)(*(int *)(param_1 + 8) + -0x10);
  }
  iVar1 = piVar2[2];
  if (iVar1 == 5) {
    *(int *)(*piVar2 + 8) = iVar3;
    if (((iVar3 != 0) && ((*(byte *)(iVar3 + 5) & 3) != 0)) && ((*(byte *)(*piVar2 + 5) & 4) != 0))
    {
      FUN_00830000(param_1,*piVar2);
    }
  }
  else if (iVar1 == 7) {
    *(int *)(*piVar2 + 8) = iVar3;
    if (((iVar3 != 0) && ((*(byte *)(iVar3 + 5) & 3) != 0)) && ((*(byte *)(*piVar2 + 5) & 4) != 0))
    {
      FUN_0083001b(param_1,*piVar2,iVar3);
    }
  }
  else {
    *(int *)(*(int *)(param_1 + 0x10) + 0x98 + iVar1 * 4) = iVar3;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return 1;
}

