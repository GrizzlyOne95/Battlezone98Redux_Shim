
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000e110(void)

{
  int unaff_EBP;
  
  DAT_1002af58 = (uint)*(byte *)(unaff_EBP + 0x20);
  DAT_1002af4c = *(undefined4 *)(unaff_EBP + 8);
  DAT_1002af50 = *(undefined4 *)(unaff_EBP + 0xc);
  DAT_1002af54 = *(undefined4 *)(unaff_EBP + 0x10);
  FUN_1000df80();
                    /* WARNING: Could not recover jumptable at 0x1000e168. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae94)();
  return;
}

