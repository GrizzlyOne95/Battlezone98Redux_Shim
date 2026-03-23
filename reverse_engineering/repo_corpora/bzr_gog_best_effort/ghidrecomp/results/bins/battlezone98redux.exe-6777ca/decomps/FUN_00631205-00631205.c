
void FUN_00631205(void)

{
  undefined4 *puVar1;
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 4;
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 0xc)) {
    *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(unaff_EBP + 8);
    puVar1 = (undefined4 *)FUN_0044f2c0();
    FUN_00631270(*puVar1);
    FUN_00631205();
    return;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

