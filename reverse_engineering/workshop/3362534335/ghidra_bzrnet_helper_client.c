
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d850(void)

{
  int unaff_EBP;
  
  *(undefined1 *)(unaff_EBP + -4) = 7;
  DAT_1002af30 = *(int **)(unaff_EBP + -0xbc);
  (**(code **)(**(int **)(unaff_EBP + -0xbc) + 0x1c))
            (DAT_1002af30 + 10,unaff_EBP + -0xa0,unaff_EBP + -0x40);
  if (DAT_1002af30 != (int *)0x0) {
    *(undefined4 *)(unaff_EBP + -4) = *(undefined4 *)(*DAT_1002af30 + 0x1c);
    (**(code **)(unaff_EBP + -4))(DAT_1002af30 + 10,&DAT_1002a234,&DAT_1002ae28);
    *(undefined4 *)(unaff_EBP + -8) = *(undefined4 *)(*DAT_1002af30 + 0x1c);
    (**(code **)(unaff_EBP + -8))(DAT_1002af30 + 10,&DAT_1002a24c,&DAT_1002a264);
  }
                    /* WARNING: Could not recover jumptable at 0x1000d8df. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae4c)();
  return;
}

