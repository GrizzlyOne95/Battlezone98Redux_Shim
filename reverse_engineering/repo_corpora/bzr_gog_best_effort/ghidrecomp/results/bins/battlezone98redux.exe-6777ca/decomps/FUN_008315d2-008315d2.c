
void FUN_008315d2(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_3 + 1U < 0x10000000) {
    uVar1 = FUN_00838869(param_1,*(undefined4 *)(param_2 + 0xc),*(int *)(param_2 + 0x1c) << 4,
                         param_3 << 4);
  }
  else {
    uVar1 = FUN_008388ab(param_1);
  }
  *(undefined4 *)(param_2 + 0xc) = uVar1;
  if (*(int *)(param_2 + 0x1c) < param_3) {
    iVar2 = *(int *)(param_2 + 0x1c) << 4;
    iVar3 = param_3 - *(int *)(param_2 + 0x1c);
    do {
      iVar2 = iVar2 + 0x10;
      *(undefined4 *)(*(int *)(param_2 + 0xc) + -8 + iVar2) = 0;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  *(int *)(param_2 + 0x1c) = param_3;
  return;
}

