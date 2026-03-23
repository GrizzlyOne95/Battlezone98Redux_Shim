
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004d22f0(void)

{
  undefined2 uVar1;
  int iVar2;
  
  uVar1 = FUN_00572d90();
  iVar2 = FUN_005771b0(uVar1);
  if (iVar2 != 0) {
    FUN_005e0bc0(*(undefined1 *)(iVar2 + 0x68));
    _DAT_0091564c = 1;
  }
  return;
}

