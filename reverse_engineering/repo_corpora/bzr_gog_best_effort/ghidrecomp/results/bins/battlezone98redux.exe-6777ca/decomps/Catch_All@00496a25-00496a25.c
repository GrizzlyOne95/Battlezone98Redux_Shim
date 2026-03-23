
void Catch_All_00496a25(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8)) {
    destroy<>(*(undefined4 *)(unaff_EBP + -0x14));
    FUN_00496a27();
    return;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

