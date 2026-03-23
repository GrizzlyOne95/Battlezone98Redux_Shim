
void FUN_008333ea(int param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  bVar1 = *(byte *)(param_1 + 0x38);
  uVar2 = *(uint *)(param_1 + 0x18);
  *(uint *)(param_1 + 0x18) = param_2;
  if (((bVar1 & 8) != 0) && (*(int *)(param_1 + 0x40) == 0)) {
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x3c);
    FUN_0082f0d6(param_1,3,0xffffffff);
  }
  if ((bVar1 & 4) != 0) {
    iVar3 = *(int *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0x10);
    iVar4 = *(int *)(iVar3 + 0xc);
    iVar6 = ((int)(param_2 - iVar4) >> 2) + -1;
    iVar3 = *(int *)(iVar3 + 0x14);
    if (iVar3 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(iVar3 + iVar6 * 4);
    }
    if ((iVar6 != 0) && (uVar2 < param_2)) {
      if (iVar3 != 0) {
        iVar7 = *(int *)(iVar3 + -4 + ((int)(uVar2 - iVar4) >> 2) * 4);
      }
      if (iVar5 == iVar7) {
        return;
      }
    }
    FUN_0082f0d6(param_1,2,iVar5);
  }
  return;
}

