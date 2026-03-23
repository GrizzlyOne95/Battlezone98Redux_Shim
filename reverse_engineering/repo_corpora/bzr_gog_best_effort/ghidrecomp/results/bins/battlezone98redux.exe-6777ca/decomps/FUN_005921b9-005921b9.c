
void FUN_005921b9(void)

{
  int iVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_0046b240();
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       (*(int *)(unaff_EBP + 8) - iVar1) * 0x10 + *(int *)(*(int *)(unaff_EBP + -0x18) + 4);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

