
void FUN_00830068(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x10);
  *(undefined1 *)(piVar1 + 5) = 0x43;
  FUN_008305c7(param_1,piVar1 + 7,0xfffffffd);
  iVar2 = 0;
  if (0 < piVar1[2]) {
    do {
      FUN_008305c7(param_1,*piVar1 + iVar2 * 4,0xfffffffd);
      iVar2 = iVar2 + 1;
    } while (iVar2 < piVar1[2]);
  }
  return;
}

