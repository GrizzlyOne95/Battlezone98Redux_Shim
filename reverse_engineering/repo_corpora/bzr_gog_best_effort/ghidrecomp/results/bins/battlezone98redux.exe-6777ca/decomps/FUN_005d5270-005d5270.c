
undefined4 FUN_005d5270(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_00918318 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0043ac30(DAT_00918318);
    if (iVar2 == 0) {
      DAT_00918318 = 0;
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

