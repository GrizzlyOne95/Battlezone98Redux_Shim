
undefined4 __fastcall FUN_00766770(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x3c) < 1) {
    if (*(int *)(param_1 + 0x3c) == 0) {
      iVar2 = FUN_00766f80();
      *(int *)(param_1 + 0x3c) = iVar2 + -1;
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
    uVar1 = 1;
  }
  return uVar1;
}

