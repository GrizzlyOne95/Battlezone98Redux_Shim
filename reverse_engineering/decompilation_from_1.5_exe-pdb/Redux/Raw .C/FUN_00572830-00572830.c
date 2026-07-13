
/* WARNING: Removing unreachable block (ram,0x00572926) */

bool FUN_00572830(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  longlong lVar5;
  int local_14;
  
  FUN_00572650();
  iVar1 = FUN_0056f760(0);
  if (DAT_00917f8e == '\0') {
    bVar4 = true;
  }
  else {
    uVar2 = FUN_0081e820("Net: Starting clients together\n");
    FUN_0081e710(uVar2);
    *(undefined1 *)(DAT_00917f48 + 0x864) = 1;
    FUN_007d6a70("sentsencs started\n");
    DAT_02a13bb4 = 0;
    FUN_00572450("Sync Start");
    local_14 = iVar1;
    while ((*(char *)(DAT_00917f48 + 0x864) != '\0' && (iVar3 = FUN_005715d0(), iVar3 != 0))) {
      FUN_00617b20();
      FUN_006192b0(&DAT_02cecee0);
      FUN_005d50a0();
      lVar5 = FUN_0056f760(0);
      local_14 = (int)lVar5;
      if ((DAT_00917f4e != '\0') || (0x5a < lVar5 - CONCAT44(DAT_00917f94,DAT_00917f90))) break;
    }
    FUN_00572450("Sync Start Complete");
    bVar4 = *(char *)(DAT_00917f48 + 0x864) == '\0';
    *(undefined1 *)(DAT_00917f48 + 0x864) = 0;
    uVar2 = FUN_0081e820("Net: Done Starting clients\n",local_14 - iVar1);
    FUN_0081e710(uVar2);
  }
  return bVar4;
}

