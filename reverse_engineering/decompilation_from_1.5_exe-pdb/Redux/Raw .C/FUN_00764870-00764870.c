
undefined4 FUN_00764870(void)

{
  int iVar1;
  
  if ((DAT_008f0470 == 2) && (iVar1 = FUN_00764810(), iVar1 != 0)) {
    return 1;
  }
  if ((DAT_008f0470 == 1) && (iVar1 = FUN_007647f0(), iVar1 != 0)) {
    return 1;
  }
  if (((DAT_008f0470 == 3) && (iVar1 = FUN_00764810(), iVar1 != 0)) &&
     (iVar1 = FUN_007647f0(), iVar1 != 0)) {
    return 1;
  }
  if (((DAT_008f0470 == 4) && (iVar1 = FUN_007647f0(), iVar1 != 0)) &&
     (iVar1 = FUN_00764840(), iVar1 != 0)) {
    return 1;
  }
  if (((DAT_008f0470 == 4) && (iVar1 = FUN_00764810(), iVar1 != 0)) &&
     (iVar1 = FUN_00764840(), iVar1 != 0)) {
    return 1;
  }
  return 0;
}

