
int FUN_0082cac6(int param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    FUN_00830222(param_1);
  }
  uVar2 = FUN_0082c489(param_1);
  iVar3 = FUN_00830a95(param_1,param_2,uVar2);
  piVar1 = *(int **)(param_1 + 8);
  *piVar1 = iVar3;
  piVar1[2] = 7;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return iVar3 + 0x18;
}

