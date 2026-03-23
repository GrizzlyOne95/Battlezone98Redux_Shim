
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00822a70(void)

{
  int iVar1;
  
  iVar1 = FUN_00572a70();
  if ((iVar1 == 0) && (DAT_02cc1b1c == 0)) {
    _DAT_02cc1b38 = FUN_00822e60();
    _DAT_02cc1b38 = _DAT_02cc1b38 - DAT_02cc1b20;
    DAT_02cc1b1c = 1;
  }
  return;
}

