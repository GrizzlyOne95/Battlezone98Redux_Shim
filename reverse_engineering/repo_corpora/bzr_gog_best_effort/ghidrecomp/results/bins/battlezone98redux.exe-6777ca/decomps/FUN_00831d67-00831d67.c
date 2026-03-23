
undefined4 FUN_00831d67(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = FUN_008334a2(param_1,param_2,param_4);
  if (*(int *)(iVar2 + 8) != 0) {
    uVar3 = FUN_008334a2(param_1,param_3,param_4);
    iVar4 = FUN_0082eafa(iVar2,uVar3);
    if (iVar4 != 0) {
      FUN_00831c7a(param_1,*(undefined4 *)(param_1 + 8),iVar2,param_2,param_3);
      piVar1 = *(int **)(param_1 + 8);
      if (piVar1[2] != 0) {
        if (piVar1[2] != 1) {
          return 1;
        }
        if (*piVar1 != 0) {
          return 1;
        }
      }
      return 0;
    }
  }
  return 0xffffffff;
}

