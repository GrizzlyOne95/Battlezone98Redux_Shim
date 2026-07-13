
void __fastcall FUN_005e4740(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x234) != 0) {
    iVar1 = FUN_0043ac70(*(int *)(param_1 + 0xf8) + 0x19c,*(undefined4 *)(param_1 + 0xf4));
    if (iVar1 != 0) {
      *(int *)(param_1 + 0x234) = iVar1;
      FUN_0043aaa0(*(undefined4 *)(param_1 + 0x234));
    }
    *(undefined4 *)(param_1 + 0x234) = 0;
  }
  return;
}

