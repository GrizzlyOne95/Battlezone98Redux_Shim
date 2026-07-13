
undefined4 FUN_0043b4f0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x3c) == 1) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043c120(param_1);
    if (*(int *)(param_1 + 0x38) < iVar2) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

