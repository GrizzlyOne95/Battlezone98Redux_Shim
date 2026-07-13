
void FUN_00831856(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = param_2;
  iVar2 = param_1;
  if (*(int *)(param_2 + 0xc) == 0) {
    param_2 = *(int *)(param_1 + 0x30);
  }
  else {
    param_2 = 0;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x14);
  FUN_008319c8(param_2,iVar3);
  FUN_00831758(uVar1,param_2 << 2,iVar3);
  if (*(int *)(iVar3 + 0xc) == 0) {
    param_2 = *(int *)(param_1 + 0x38);
  }
  else {
    param_2 = 0;
  }
  FUN_008319c8(param_2,iVar3);
  if (0 < param_2) {
    param_1 = 0;
    do {
      FUN_008319de(*(undefined4 *)(param_1 + *(int *)(iVar2 + 0x18)),iVar3);
      FUN_008319c8(*(undefined4 *)(param_1 + 4 + *(int *)(iVar2 + 0x18)),iVar3);
      FUN_008319c8(*(undefined4 *)(param_1 + 8 + *(int *)(iVar2 + 0x18)),iVar3);
      param_1 = param_1 + 0xc;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  iVar5 = 0;
  iVar4 = iVar5;
  if (*(int *)(iVar3 + 0xc) == 0) {
    iVar4 = *(int *)(iVar2 + 0x24);
  }
  FUN_008319c8(iVar4,iVar3);
  if (0 < iVar4) {
    do {
      FUN_008319de(*(undefined4 *)(*(int *)(iVar2 + 0x1c) + iVar5 * 4),iVar3);
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar4);
  }
  return;
}

