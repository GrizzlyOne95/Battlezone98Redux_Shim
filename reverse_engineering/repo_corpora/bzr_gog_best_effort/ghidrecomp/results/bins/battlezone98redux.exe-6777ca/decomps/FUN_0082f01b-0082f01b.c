
void FUN_0082f01b(int param_1)

{
  code *pcVar1;
  
  if (*(int *)(param_1 + 0x30) < 0x4e21) {
    FUN_0082f536(param_1,*(int *)(param_1 + 0x30) * 2);
    if (20000 < *(int *)(param_1 + 0x30)) {
      FUN_0082df5b(param_1,"stack overflow");
    }
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 0x18;
    return;
  }
  FUN_0082f657(param_1,5);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

