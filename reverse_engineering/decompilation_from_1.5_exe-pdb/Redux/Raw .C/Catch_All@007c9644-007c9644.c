
void Catch_All_007c9644(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (1 < *(int *)(unaff_EBP + -0x20)) {
    FID_conflict__Destroy
              (*(undefined4 *)(unaff_EBP + -0x1c),
               *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x24) * 4);
  }
  if (0 < *(int *)(unaff_EBP + -0x20)) {
    FID_conflict__Destroy
              (*(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x24) * 4,
               *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x24) * 4 +
               *(int *)(unaff_EBP + 0x10) * 4);
  }
  uVar2 = *(undefined4 *)(unaff_EBP + -0x2c);
  uVar1 = *(undefined4 *)(unaff_EBP + -0x1c);
  Getal(unaff_EBP + -0x12);
  deallocate(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

