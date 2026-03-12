
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10022480(void)

{
  void *pvVar1;
  
  if (0xf < DAT_1002a218) {
    pvVar1 = DAT_1002a204;
    if (0xfff < DAT_1002a218 + 1) {
      pvVar1 = *(void **)((int)DAT_1002a204 + -4);
      if (0x1f < (uint)((int)DAT_1002a204 + (-4 - (int)pvVar1))) {
                    /* WARNING: Could not recover jumptable at 0x100224ac. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
        _invalid_parameter_noinfo_noreturn();
        return;
      }
    }
    FUN_1001f9a8(pvVar1);
  }
  _DAT_1002a214 = 0;
  DAT_1002a218 = 0xf;
  DAT_1002a204 = (void *)((uint)DAT_1002a204 & 0xffffff00);
  return;
}

