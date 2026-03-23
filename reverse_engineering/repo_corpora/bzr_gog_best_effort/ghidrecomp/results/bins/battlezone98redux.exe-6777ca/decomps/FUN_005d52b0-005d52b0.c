
undefined4 FUN_005d52b0(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_00918318 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043ac30(DAT_00918318);
    if (iVar2 != 0) {
      FUN_0043abf0(DAT_00918318);
    }
    DAT_00918318 = 0;
    uVar1 = 1;
  }
  return uVar1;
}

