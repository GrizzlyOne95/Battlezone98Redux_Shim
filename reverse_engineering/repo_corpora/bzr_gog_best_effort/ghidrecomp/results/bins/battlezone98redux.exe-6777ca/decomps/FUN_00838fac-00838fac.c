
undefined4 FUN_00838fac(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x34);
  uVar2 = FUN_008309f4(iVar1,param_2,param_3);
  puVar3 = (undefined4 *)FUN_00831159(iVar1,*(undefined4 *)(*(int *)(param_1 + 0x30) + 4),uVar2);
  if (puVar3[2] == 0) {
    *puVar3 = 1;
    puVar3[2] = 1;
    if (*(uint *)(*(int *)(iVar1 + 0x10) + 0x40) <= *(uint *)(*(int *)(iVar1 + 0x10) + 0x44)) {
      FUN_00830222(iVar1);
    }
  }
  return uVar2;
}

