
void Catch_All_0071a2be(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -0x30) = *(undefined4 *)(unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(unaff_EBP + -0x30);
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    *(undefined4 *)(unaff_EBP + -0x34) = 0;
  }
  else {
    uVar1 = FUN_0071b520(1);
    *(undefined4 *)(unaff_EBP + -0x34) = uVar1;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

