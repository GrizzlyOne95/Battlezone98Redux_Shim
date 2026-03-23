
undefined4 FUN_005773f0(undefined2 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = FUN_005771b0(param_1);
  uVar3 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_00822d90();
    *(undefined4 *)(iVar1 + 0x60) = uVar2;
    *(undefined4 *)(iVar1 + 100) = 0;
    uVar3 = *(uint *)(iVar1 + 0x60) | *(uint *)(iVar1 + 100);
    if (uVar3 == 0) {
      *(undefined4 *)(iVar1 + 0x60) = 1;
      *(undefined4 *)(iVar1 + 100) = 0;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),iVar1 != 0);
}

