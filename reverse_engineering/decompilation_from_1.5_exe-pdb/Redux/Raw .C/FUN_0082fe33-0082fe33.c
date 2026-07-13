
void FUN_0082fe33(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if ((*(uint *)(iVar1 + 4) <
       (uint)((int)(*(int *)(iVar1 + 8) + (*(int *)(iVar1 + 8) >> 0x1f & 3U)) >> 2)) &&
     (0x40 < *(int *)(iVar1 + 8))) {
    FUN_00830af4(param_1,*(int *)(iVar1 + 8) / 2);
  }
  if (0x40 < *(uint *)(iVar1 + 0x3c)) {
    uVar3 = *(uint *)(iVar1 + 0x3c) >> 1;
    if (uVar3 + 1 < 0xfffffffe) {
      uVar2 = FUN_00838869(param_1,*(undefined4 *)(iVar1 + 0x34),*(undefined4 *)(iVar1 + 0x3c),uVar3
                          );
    }
    else {
      uVar2 = FUN_008388ab(param_1);
    }
    *(uint *)(iVar1 + 0x3c) = uVar3;
    *(undefined4 *)(iVar1 + 0x34) = uVar2;
  }
  return;
}

