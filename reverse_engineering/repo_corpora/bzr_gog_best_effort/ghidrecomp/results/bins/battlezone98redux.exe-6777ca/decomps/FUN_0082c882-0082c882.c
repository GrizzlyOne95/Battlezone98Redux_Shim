
bool FUN_0082c882(int param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar2 = piVar1[2];
  if ((iVar2 == 5) || (iVar2 == 7)) {
    iVar2 = *(int *)(*piVar1 + 8);
  }
  else {
    iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 0x98 + iVar2 * 4);
  }
  if (iVar2 != 0) {
    piVar1 = *(int **)(param_1 + 8);
    *piVar1 = iVar2;
    piVar1[2] = 5;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  }
  return iVar2 != 0;
}

