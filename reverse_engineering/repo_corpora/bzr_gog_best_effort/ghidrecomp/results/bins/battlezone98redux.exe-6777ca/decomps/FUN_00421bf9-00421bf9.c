
void FUN_00421bf9(void)

{
  int iVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = size();
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       *(int *)(*(int *)(unaff_EBP + -0x18) + 4) + (*(int *)(unaff_EBP + 8) - iVar1) * 4;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

