
undefined4 FUN_00830c97(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = FUN_00830c5b(param_1);
  if (iVar2 - 1U < 0x4000000) {
    iVar2 = FUN_0082e8a8(iVar2 + -1);
    piVar1 = (int *)(param_2 + iVar2 * 4 + 4);
    *piVar1 = *piVar1 + 1;
    return 1;
  }
  return 0;
}

