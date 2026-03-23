
undefined1 FUN_004181c0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_10;
  
  iVar2 = FUN_00417c70();
  if (iVar2 == 0) {
    return 0;
  }
  uVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
  iVar4 = FUN_00417e20(uVar3);
  if (iVar4 != 0) {
    if ((iVar2 == 0) || (cVar1 = FUN_00417dd0(), cVar1 == '\0')) {
      local_10 = 0;
    }
    else {
      local_10 = 1;
    }
    return local_10;
  }
  return 0;
}

