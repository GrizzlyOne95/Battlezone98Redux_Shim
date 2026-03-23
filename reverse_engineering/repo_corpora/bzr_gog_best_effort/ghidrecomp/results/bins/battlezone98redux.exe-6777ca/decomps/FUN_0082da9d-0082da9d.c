
undefined4 FUN_0082da9d(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_0082dad3(param_1,param_2);
  if (iVar2 < 0) {
    uVar3 = 0xffffffff;
  }
  else {
    iVar1 = *(int *)(*(int *)(**(int **)(param_2 + 4) + 0x10) + 0x14);
    if (iVar1 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = *(undefined4 *)(iVar1 + iVar2 * 4);
    }
  }
  return uVar3;
}

