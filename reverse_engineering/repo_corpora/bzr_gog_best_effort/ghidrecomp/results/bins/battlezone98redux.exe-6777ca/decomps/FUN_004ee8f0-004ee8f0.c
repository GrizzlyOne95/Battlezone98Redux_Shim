
void __fastcall FUN_004ee8f0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xf8);
  if (*(int *)(param_1 + 0x2c4) != 0) {
    iVar1 = FUN_0043ac70(iVar2 + 0x5b0,*(undefined4 *)(param_1 + 0xf4));
    if (iVar1 != 0) {
      *(int *)(param_1 + 0x2c4) = iVar1;
      FUN_0043aaa0(*(undefined4 *)(param_1 + 0x2c4));
    }
    *(undefined4 *)(param_1 + 0x2c4) = 0;
  }
  if (*(int *)(param_1 + 0x2c0) != 0) {
    iVar1 = FUN_0043ac70(iVar2 + 0x5a0,*(undefined4 *)(param_1 + 0xf4));
    if (iVar1 != 0) {
      *(int *)(param_1 + 0x2c0) = iVar1;
      FUN_0043aaa0(*(undefined4 *)(param_1 + 0x2c0));
    }
    *(undefined4 *)(param_1 + 0x2c0) = 0;
  }
  if (*(int *)(param_1 + 0x2cc) != 0) {
    iVar2 = FUN_0043ac70(iVar2 + 0x5c0,*(undefined4 *)(param_1 + 0xf4));
    if (iVar2 != 0) {
      *(int *)(param_1 + 0x2cc) = iVar2;
      FUN_0043aaa0(*(undefined4 *)(param_1 + 0x2cc));
    }
    *(undefined4 *)(param_1 + 0x2cc) = 0;
  }
  return;
}

