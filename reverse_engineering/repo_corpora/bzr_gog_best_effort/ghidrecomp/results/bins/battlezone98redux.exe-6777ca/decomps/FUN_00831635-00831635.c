
void FUN_00831635(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (param_3 == 0) {
    iVar4 = 0;
    *(undefined **)(param_2 + 0x10) = &DAT_0086eef0;
    iVar5 = 0;
  }
  else {
    iVar4 = FUN_0082e8a8(param_3 + -1);
    iVar4 = iVar4 + 1;
    if (0x1a < iVar4) {
      FUN_0082df5b(param_1,"table overflow");
    }
    iVar5 = 1 << ((byte)iVar4 & 0x1f);
    if (iVar5 + 1U < 0x8000000) {
      uVar1 = FUN_00838869(param_1,0,0,iVar5 << 5);
    }
    else {
      uVar1 = FUN_008388ab(param_1);
    }
    *(undefined4 *)(param_2 + 0x10) = uVar1;
    if (0 < iVar5) {
      iVar3 = 0;
      iVar6 = iVar5;
      do {
        iVar2 = *(int *)(param_2 + 0x10) + iVar3;
        iVar3 = iVar3 + 0x20;
        *(undefined4 *)(iVar2 + 0x1c) = 0;
        *(undefined4 *)(iVar2 + 0x18) = 0;
        *(undefined4 *)(iVar2 + 8) = 0;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  *(int *)(param_2 + 0x14) = iVar5 * 0x20 + *(int *)(param_2 + 0x10);
  *(char *)(param_2 + 7) = (char)iVar4;
  return;
}

