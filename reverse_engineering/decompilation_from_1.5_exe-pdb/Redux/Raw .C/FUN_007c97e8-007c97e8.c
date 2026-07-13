
undefined4 FUN_007c97e8(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       *(int *)(*(int *)(unaff_EBP + -0x18) + 4) + *(int *)(unaff_EBP + 0x10) * 4;
  FUN_00422c10(*(undefined4 *)(unaff_EBP + 0xc),*(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 4));
  FUN_007c9930(*(undefined4 *)(unaff_EBP + 0xc),
               *(int *)(*(int *)(unaff_EBP + -0x18) + 4) + *(int *)(unaff_EBP + 0x10) * -4,
               unaff_EBP + -0x30);
  uVar2 = *(undefined4 *)(unaff_EBP + -0x38);
  uVar1 = *(undefined4 *)(unaff_EBP + 8);
  FID_conflict_begin(unaff_EBP + -0x3c);
  FID_conflict_operator_(uVar1,uVar2);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

