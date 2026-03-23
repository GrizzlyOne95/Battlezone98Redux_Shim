
void FUN_0083b96c(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = param_2;
  iVar2 = FUN_0083bbeb(param_1);
  if (iVar2 + 1U < 0x40000000) {
    uVar3 = FUN_00838869(*param_1,0,0,iVar2 << 2);
  }
  else {
    uVar3 = FUN_008388ab(*param_1);
  }
  *(int *)(param_2 + 0x30) = iVar2;
  *(undefined4 *)(param_2 + 0x14) = uVar3;
  FUN_0083b798(param_1,uVar3,iVar2 << 2);
  iVar2 = FUN_0083bbeb(param_1);
  if (iVar2 + 1U < 0x15555556) {
    uVar3 = FUN_00838869(*param_1,0,0,iVar2 * 0xc);
  }
  else {
    uVar3 = FUN_008388ab(*param_1);
  }
  *(undefined4 *)(param_2 + 0x18) = uVar3;
  *(int *)(param_2 + 0x38) = iVar2;
  if (0 < iVar2) {
    iVar4 = 0;
    iVar5 = iVar2;
    do {
      *(undefined4 *)(iVar4 + *(int *)(param_2 + 0x18)) = 0;
      iVar4 = iVar4 + 0xc;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (0 < iVar2) {
      param_2 = 0;
      do {
        uVar3 = FUN_0083bc1d(param_1);
        *(undefined4 *)(param_2 + *(int *)(iVar1 + 0x18)) = uVar3;
        uVar3 = FUN_0083bbeb(param_1);
        *(undefined4 *)(param_2 + 4 + *(int *)(iVar1 + 0x18)) = uVar3;
        uVar3 = FUN_0083bbeb(param_1);
        *(undefined4 *)(param_2 + 8 + *(int *)(iVar1 + 0x18)) = uVar3;
        param_2 = param_2 + 0xc;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  iVar4 = 0;
  iVar2 = FUN_0083bbeb(param_1);
  if (iVar2 + 1U < 0x40000000) {
    uVar3 = FUN_00838869(*param_1,0,0,iVar2 << 2);
  }
  else {
    uVar3 = FUN_008388ab(*param_1);
  }
  *(undefined4 *)(iVar1 + 0x1c) = uVar3;
  *(int *)(iVar1 + 0x24) = iVar2;
  iVar5 = iVar4;
  if (0 < iVar2) {
    do {
      *(undefined4 *)(*(int *)(iVar1 + 0x1c) + iVar5 * 4) = 0;
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar2);
    if (0 < iVar2) {
      do {
        uVar3 = FUN_0083bc1d(param_1);
        *(undefined4 *)(*(int *)(iVar1 + 0x1c) + iVar4 * 4) = uVar3;
        iVar4 = iVar4 + 1;
      } while (iVar4 < iVar2);
    }
  }
  return;
}

