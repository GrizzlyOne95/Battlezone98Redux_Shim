
void FUN_00812f41(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  FUN_0045ba10(*(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 4));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

