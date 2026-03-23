
void FUN_0082da0c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  if ((param_2 == 0) || (*(char *)(param_2 + 6) != '\0')) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
  }
  else {
    iVar4 = 0;
    uVar2 = FUN_00830f66(param_1,0,0);
    iVar1 = *(int *)(*(int *)(param_2 + 0x10) + 0x14);
    if (0 < *(int *)(*(int *)(param_2 + 0x10) + 0x30)) {
      do {
        puVar3 = (undefined4 *)FUN_00831114(param_1,uVar2,*(undefined4 *)(iVar1 + iVar4 * 4));
        iVar4 = iVar4 + 1;
        *puVar3 = 1;
        puVar3[2] = 1;
      } while (iVar4 < *(int *)(*(int *)(param_2 + 0x10) + 0x30));
    }
    puVar3 = *(undefined4 **)(param_1 + 8);
    *puVar3 = uVar2;
    puVar3[2] = 5;
  }
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
    FUN_0082f194(param_1,1);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

