
void FUN_007ceffe(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(unaff_EBP + -4) = 2;
  *(int *)(*(int *)(unaff_EBP + -0x48) + 4) =
       *(int *)(unaff_EBP + 0x10) * 0x18 + *(int *)(*(int *)(unaff_EBP + -0x48) + 4);
  FUN_00422c10(*(undefined4 *)(unaff_EBP + 0xc),*(undefined4 *)(*(int *)(unaff_EBP + -0x48) + 4));
  FUN_007cf1f0(*(undefined4 *)(unaff_EBP + 0xc),
               *(int *)(*(int *)(unaff_EBP + -0x48) + 4) + *(int *)(unaff_EBP + 0x10) * -0x18,
               unaff_EBP + -0x2c);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  ~basic_string<>();
  uVar2 = *(undefined4 *)(unaff_EBP + -100);
  uVar1 = *(undefined4 *)(unaff_EBP + 8);
  FID_conflict_begin(unaff_EBP + -0x68);
  FID_conflict_operator_(uVar1,uVar2);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

