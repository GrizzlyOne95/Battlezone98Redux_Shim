
undefined4 FUN_0070bfbd(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00703d50();
  *(undefined1 *)(unaff_EBP + -0x11) = 0;
  *(int *)(unaff_EBP + -0x30) = unaff_EBP + -0x11;
  uVar1 = FUN_00417780(*(undefined4 *)(unaff_EBP + -0x18));
  *(undefined4 *)(unaff_EBP + -0x34) = uVar1;
  uVar1 = forward<>(0xc,*(undefined4 *)(unaff_EBP + -0x34),**(undefined1 **)(unaff_EBP + -0x30));
  *(undefined4 *)(unaff_EBP + -0x24) = uVar1;
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (*(int *)(unaff_EBP + -0x24) == 0) {
    *(undefined4 *)(unaff_EBP + -0x28) = 0;
  }
  else {
    uVar1 = FUN_00710210();
    *(undefined4 *)(unaff_EBP + -0x28) = uVar1;
  }
  *(undefined4 *)(unaff_EBP + -0x3c) = *(undefined4 *)(unaff_EBP + -0x28);
  *(undefined1 *)(unaff_EBP + -4) = 0;
  *(undefined4 *)(unaff_EBP + -0x38) = *(undefined4 *)(unaff_EBP + -0x18);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  FUN_00711860();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + -0x38);
}

