
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d460(void)

{
  int unaff_EBP;
  undefined4 unaff_retaddr;
  
  *(undefined4 *)(unaff_EBP + -4) = unaff_retaddr;
  (*DAT_1002adfc)();
  (*DAT_1002ae00)(*(undefined4 *)(unaff_EBP + -4));
                    /* WARNING: Could not recover jumptable at 0x1000d478. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae08)();
  return;
}

