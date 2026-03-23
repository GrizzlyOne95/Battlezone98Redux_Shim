
uint FUN_00830e70(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = *(uint *)(param_1 + 0x1c);
  if ((uVar3 == 0) || (*(int *)(*(int *)(param_1 + 0xc) + -8 + uVar3 * 0x10) != 0)) {
    if (*(undefined **)(param_1 + 0x10) != &DAT_0086eef0) {
      uVar3 = FUN_008316d8(param_1,uVar3);
    }
  }
  else {
    uVar1 = uVar3;
    uVar4 = 0;
    uVar2 = uVar3;
    while (uVar3 = uVar4, 1 < uVar2) {
      uVar4 = uVar3 + uVar1 >> 1;
      if (*(int *)(*(int *)(param_1 + 0xc) + -8 + uVar4 * 0x10) != 0) {
        uVar3 = uVar4;
        uVar4 = uVar1;
      }
      uVar2 = uVar4 - uVar3;
      uVar1 = uVar4;
      uVar4 = uVar3;
    }
  }
  return uVar3;
}

