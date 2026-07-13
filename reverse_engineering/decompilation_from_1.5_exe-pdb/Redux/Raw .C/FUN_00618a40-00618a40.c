
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00618a40(void)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_006185b0();
  FUN_0081e0c0("Start of Game Menu Display\n");
  iVar1 = FUN_004341c0();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    DAT_008eaaa8 = 0;
    iVar1 = FUN_006185f0();
    if (iVar1 == 0) {
      _DAT_009183e4 = 1;
      while( true ) {
        iVar1 = FUN_00434160();
        if (iVar1 != 5) break;
        FUN_00618270(0);
      }
      FUN_00618970();
      _DAT_009183e4 = 0;
      uVar2 = 1;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

