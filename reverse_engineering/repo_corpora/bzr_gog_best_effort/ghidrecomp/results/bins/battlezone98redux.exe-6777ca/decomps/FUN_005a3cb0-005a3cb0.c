
void __fastcall FUN_005a3cb0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    uVar1 = FUN_005a3b40(*(undefined4 *)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x80) = uVar1;
    if (*(int *)(param_1 + 0x80) != 0) {
      *(undefined4 *)(param_1 + 0x20) = 0x10;
    }
  }
  FUN_00583c80();
  *(undefined1 *)(param_1 + 0x7c) = 0;
  return;
}

