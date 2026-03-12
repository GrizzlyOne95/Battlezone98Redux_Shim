
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d7b0(void)

{
  int unaff_EBP;
  
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  DAT_1002af2c = *(int **)(unaff_EBP + -0x26c);
  (**(code **)(**(int **)(unaff_EBP + -0x26c) + 0x1c))
            (DAT_1002af2c + 10,unaff_EBP + -0xb8,unaff_EBP + -0x100);
  if (DAT_1002af2c != (int *)0x0) {
    *(undefined4 *)(unaff_EBP + -4) = *(undefined4 *)(*DAT_1002af2c + 0x1c);
    (**(code **)(unaff_EBP + -4))(DAT_1002af2c + 10,&DAT_1002a234,&DAT_1002ae28);
    *(undefined4 *)(unaff_EBP + -8) = *(undefined4 *)(*DAT_1002af2c + 0x1c);
    (**(code **)(unaff_EBP + -8))(DAT_1002af2c + 10,&DAT_1002a24c,&DAT_1002a264);
  }
                    /* WARNING: Could not recover jumptable at 0x1000d843. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae44)();
  return;
}

