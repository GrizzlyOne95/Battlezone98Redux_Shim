
void Catch_All_007a2ee4(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  undefined4 uVar2;
  
  *(undefined4 *)(unaff_EBP + -0x34) = *(undefined4 *)(unaff_EBP + 8);
  FUN_0042dd10(*(undefined4 *)(unaff_EBP + -0x34));
  uVar1 = FUN_00417780(*(undefined4 *)(unaff_EBP + 8));
  uVar1 = FUN_00417780(uVar1);
  Getal(unaff_EBP + -0x13);
  destroy<>(uVar1);
  uVar1 = FUN_004242e0(*(undefined4 *)(unaff_EBP + 8));
  uVar1 = FUN_00417780(uVar1);
  Getal(unaff_EBP + -0x14);
  destroy<>(uVar1);
  uVar2 = 1;
  uVar1 = *(undefined4 *)(unaff_EBP + 8);
  Getal(unaff_EBP + -0x15);
  deallocate(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

