
void Catch_All_00736224(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  FUN_0072d510(unaff_EBP + -0x18);
  while( true ) {
    uVar1 = FUN_0072d580();
    *(undefined4 *)(unaff_EBP + -0x18) = uVar1;
    if (*(int *)(unaff_EBP + -0x18) == 0) break;
    FUN_0072d510(unaff_EBP + -0x18);
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

