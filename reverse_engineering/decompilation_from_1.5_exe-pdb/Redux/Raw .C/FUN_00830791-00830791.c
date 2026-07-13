
void FUN_00830791(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *extraout_EDX;
  int *piVar4;
  int *piVar5;
  
  if ((3 < *(int *)(param_2 + 0x50)) && ((*(byte *)(*(int *)(param_2 + 0x48) + 5) & 3) != 0)) {
    FUN_00830437(param_1,*(int *)(param_2 + 0x48));
  }
  piVar5 = *(int **)(param_2 + 8);
  for (uVar3 = *(uint *)(param_2 + 0x28); uVar3 <= *(uint *)(param_2 + 0x14); uVar3 = uVar3 + 0x18)
  {
    if (piVar5 < *(int **)(uVar3 + 8)) {
      piVar5 = *(int **)(uVar3 + 8);
    }
  }
  for (piVar4 = *(int **)(param_2 + 0x20); piVar4 < *(int **)(param_2 + 8); piVar4 = piVar4 + 4) {
    if ((3 < piVar4[2]) && ((*(byte *)(*piVar4 + 5) & 3) != 0)) {
      FUN_00830437(param_1,*piVar4);
      piVar4 = extraout_EDX;
    }
  }
  for (; piVar4 <= piVar5; piVar4 = piVar4 + 4) {
    piVar4[2] = 0;
  }
  iVar1 = *(int *)(param_2 + 0x20);
  iVar2 = *(int *)(param_2 + 0x30);
  if (iVar2 < 0x4e21) {
    if ((((*(int *)(param_2 + 0x14) - *(int *)(param_2 + 0x28)) / 0x18) * 4 < iVar2) &&
       (0x10 < iVar2)) {
      FUN_0082f536(param_2,iVar2 / 2);
    }
    iVar2 = *(int *)(param_2 + 0x2c);
    if ((((int)piVar5 - iVar1 >> 4) * 4 < iVar2) && (0x5a < iVar2)) {
      FUN_0082f596(param_2,iVar2 / 2);
    }
  }
  return;
}

