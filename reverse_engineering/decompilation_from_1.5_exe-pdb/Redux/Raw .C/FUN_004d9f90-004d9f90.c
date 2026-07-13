
undefined * FUN_004d9f90(void)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  if (DAT_02a0db20 < 0) {
    cVar1 = FUN_0041fc90();
    if (cVar1 == '\0') {
      piVar2 = (int *)FUN_004e0020();
      (**(code **)(*(int *)(*piVar2 + 0x18) + 0x10))();
    }
    if (DAT_02a0db20 < 0) {
      return (undefined *)0x0;
    }
  }
  iVar3 = DAT_02a0db20 * 0x400;
  DAT_02a0db24 = DAT_02a0db24 + -1;
  DAT_02a0db20 = *(undefined4 *)(&DAT_0260dc24 + iVar3);
  return &DAT_0260db20 + iVar3;
}

