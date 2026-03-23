
void Catch_All_007cefd4(void)

{
  int unaff_EBP;
  
  FID_conflict__Destroy
            (*(int *)(unaff_EBP + 0x10) * 0x18 + *(int *)(unaff_EBP + 0xc),
             *(int *)(unaff_EBP + 0x10) * 0x18 + *(int *)(*(int *)(unaff_EBP + -0x48) + 4));
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

