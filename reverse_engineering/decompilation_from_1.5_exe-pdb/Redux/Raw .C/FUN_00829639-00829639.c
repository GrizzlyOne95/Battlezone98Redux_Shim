
void FUN_00829639(void)

{
  int iVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_00829680();
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       (*(int *)(unaff_EBP + 8) - iVar1) * 0x1004 + *(int *)(*(int *)(unaff_EBP + -0x18) + 4);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

