
void __fastcall FUN_0050a970(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_00417c60();
  if ((*(char *)(param_1 + 0x5c) == '\0') && (*(int *)(param_1 + 0x58) != 0)) {
    FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"Start");
    iVar1 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
    if (iVar1 == 6) {
      uVar2 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),0,0,0,*(undefined4 *)(param_1 + 0x58),
                           "Lua script Start error:\n%s");
      FUN_004ff600(uVar2);
    }
    else {
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  return;
}

