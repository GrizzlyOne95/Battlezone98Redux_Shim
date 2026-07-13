
void __fastcall FUN_007a4a80(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = FUN_007cb1a0(param_1);
  if ((iVar2 != 0) && (*(char *)(iVar2 + 0x8e) == '\0')) {
    uVar1 = FUN_0056f920();
    iVar2 = FUN_00572b50(uVar1);
    if (iVar2 == 0) {
      uVar1 = FUN_0056f920();
      FUN_00572ba0(uVar1);
    }
    else {
      uVar1 = FUN_0056f920();
      FUN_00572bd0(uVar1);
    }
  }
  return;
}

