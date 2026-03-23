
void FUN_007a2bc6(void)

{
  undefined4 *puVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  puVar1 = (undefined4 *)FID_conflict_begin(unaff_EBP + -0x40);
  *(undefined4 *)(unaff_EBP + -0x30) = *puVar1;
  *(undefined4 *)(unaff_EBP + -0x34) = *(undefined4 *)(unaff_EBP + -0x1c);
  FUN_0042d970(unaff_EBP + -0x44,*(undefined4 *)(unaff_EBP + -0x34),
               *(undefined4 *)(unaff_EBP + -0x30));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

