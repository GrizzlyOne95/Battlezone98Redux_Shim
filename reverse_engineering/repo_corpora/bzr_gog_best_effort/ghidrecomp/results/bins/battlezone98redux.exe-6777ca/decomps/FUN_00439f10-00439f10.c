
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_00439f10(void)

{
  int iVar1;
  
  FUN_0081e1e0("FirstGAS Called\n");
  _DAT_0091559c = 0;
  _DAT_009155a0 = 0;
  _DAT_009155a4 = 0;
  _DAT_009155a8 = 0;
  _DAT_009155ac = 0;
  _DAT_009155b0 = 0;
  _DAT_009155b4 = 0;
  iVar1 = FUN_0043a6c0(&DAT_0091559c);
  if (iVar1 != 0) {
    DAT_00915594 = &DAT_0091559c;
    FUN_0043c2a0(&DAT_0091559c);
    FUN_0043a660(0x40);
    FUN_0043c230();
    FUN_0043a910(0xffffffff,0xffffffff,0xffffffff);
    FUN_0043bd20();
    DAT_0260c217 = 0;
  }
  return iVar1 != 0;
}

