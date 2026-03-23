
bool FUN_00577360(undefined2 param_1,byte param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = FUN_005771b0(param_1);
  if (iVar1 != 0) {
    uVar2 = FUN_00822d90();
    *(undefined4 *)(iVar1 + 0x58) = uVar2;
    *(undefined4 *)(iVar1 + 0x5c) = 0;
    if (*(int *)(iVar1 + 0x58) == 0 && *(int *)(iVar1 + 0x5c) == 0) {
      *(undefined4 *)(iVar1 + 0x58) = 1;
      *(undefined4 *)(iVar1 + 0x5c) = 0;
    }
    uVar3 = FUN_00416410();
    if (param_2 != uVar3) {
      return false;
    }
  }
  return iVar1 != 0;
}

