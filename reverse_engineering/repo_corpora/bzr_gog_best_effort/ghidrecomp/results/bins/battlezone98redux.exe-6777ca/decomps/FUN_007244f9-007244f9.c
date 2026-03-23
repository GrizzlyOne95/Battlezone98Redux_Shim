
void FUN_007244f9(void)

{
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 8;
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 0x10)) {
    destroy<>(*(undefined4 *)(unaff_EBP + -0x14));
    FUN_007244f9();
    return;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

