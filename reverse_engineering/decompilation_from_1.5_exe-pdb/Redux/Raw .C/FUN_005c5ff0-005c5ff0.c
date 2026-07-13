
uint FUN_005c5ff0(int param_1)

{
  int iVar1;
  uint local_8;
  
  if (param_1 != 0) {
    for (local_8 = 0; local_8 < 0x14; local_8 = local_8 + 1) {
      iVar1 = local_8 * 8;
      if (*(int *)(&DAT_009181c0 + iVar1) == param_1) {
        *(int *)(&DAT_009181c4 + iVar1) = *(int *)(&DAT_009181c4 + iVar1) + 1;
        return local_8;
      }
    }
  }
  return 0xffffffff;
}

