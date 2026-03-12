
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000e360(void)

{
  int unaff_EBP;
  
  DAT_1002af5c = *(undefined4 *)(unaff_EBP + -0xd8);
  FUN_1000e1f0();
  *(undefined1 *)(unaff_EBP + -4) = 0xff;
                    /* WARNING: Could not recover jumptable at 0x1000e37b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002aea8)();
  return;
}

