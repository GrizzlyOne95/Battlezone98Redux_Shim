
void Catch_All_0057c00a(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  FID_conflict__Destroy(*(undefined4 *)(unaff_EBP + -0x20),*(undefined4 *)(unaff_EBP + -0x24));
  uVar2 = *(undefined4 *)(unaff_EBP + -0x28);
  uVar1 = *(undefined4 *)(unaff_EBP + -0x20);
  Getal(unaff_EBP + -0x12);
  deallocate(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

