
void Catch_All_007cee51(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (1 < *(int *)(unaff_EBP + -0x50)) {
    FID_conflict__Destroy
              (*(undefined4 *)(unaff_EBP + -0x4c),
               *(int *)(unaff_EBP + -0x54) * 0x18 + *(int *)(unaff_EBP + -0x4c));
  }
  if (0 < *(int *)(unaff_EBP + -0x50)) {
    FID_conflict__Destroy
              (*(int *)(unaff_EBP + -0x54) * 0x18 + *(int *)(unaff_EBP + -0x4c),
               *(int *)(unaff_EBP + -0x54) * 0x18 + *(int *)(unaff_EBP + -0x4c) +
               *(int *)(unaff_EBP + 0x10) * 0x18);
  }
  uVar2 = *(undefined4 *)(unaff_EBP + -0x5c);
  uVar1 = *(undefined4 *)(unaff_EBP + -0x4c);
  Getal(unaff_EBP + -0x5e);
  deallocate(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

