
undefined4 FUN_005ce580(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (*(int *)(iVar1 + 0x300) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00477590(*(int *)(iVar1 + 0x300));
  }
  return uVar2;
}

