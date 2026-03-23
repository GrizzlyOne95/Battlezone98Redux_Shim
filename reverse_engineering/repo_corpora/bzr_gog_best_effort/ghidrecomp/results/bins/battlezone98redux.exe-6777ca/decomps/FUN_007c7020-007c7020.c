
undefined4 __fastcall FUN_007c7020(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x25) == '\0') {
    iVar2 = FUN_00434640();
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      if ((DAT_00920ed0 != 0) && (DAT_00920ecc != 0)) {
        FUN_006834b0();
      }
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

