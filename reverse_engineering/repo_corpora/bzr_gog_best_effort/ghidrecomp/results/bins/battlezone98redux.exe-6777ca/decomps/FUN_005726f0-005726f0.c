
/* WARNING: Removing unreachable block (ram,0x00572730) */

int FUN_005726f0(void)

{
  int iVar1;
  longlong lVar2;
  
  lVar2 = FUN_0056f760(0);
  if (DAT_00917f4e == '\0') {
    if ((DAT_00917f90 != 0 || DAT_00917f94 != 0) && (CONCAT44(DAT_00917f94,DAT_00917f90) <= lVar2))
    {
      iVar1 = (int)lVar2 - DAT_00917f90;
      if (0x5a < iVar1) {
        return 0;
      }
      return 0x5a - iVar1;
    }
    iVar1 = 0x5a;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

