
void FUN_007340fc(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 0x18)) {
    uVar1 = FUN_006ef1a0(unaff_EBP + -0x14);
    FUN_006ef1c0(*(undefined4 *)(unaff_EBP + 0xc),uVar1);
    FUN_007340f3();
    return;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

