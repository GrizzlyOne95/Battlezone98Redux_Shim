
undefined1 FUN_0061ffb0(char *param_1)

{
  int iVar1;
  uint local_8;
  
  if (param_1 != (char *)0x0) {
    for (local_8 = 0; local_8 < 0x2c; local_8 = local_8 + 1) {
      iVar1 = _stricmp((&PTR_s_COCKPIT_VIEW_008eb088)[local_8 * 2],param_1);
      if (iVar1 == 0) {
        return (&DAT_008eb08c)[local_8 * 8];
      }
    }
  }
  return 0;
}

