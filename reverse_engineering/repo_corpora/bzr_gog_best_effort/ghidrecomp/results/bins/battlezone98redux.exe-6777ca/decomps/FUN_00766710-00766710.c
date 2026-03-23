
undefined4 __fastcall FUN_00766710(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00766f80();
  if (*(int *)(param_1 + 0x3c) < iVar1 + -1) {
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
    uVar2 = 1;
  }
  else if (*(int *)(param_1 + 0x3c) == iVar1 + -1) {
    *(undefined4 *)(param_1 + 0x3c) = 0;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

