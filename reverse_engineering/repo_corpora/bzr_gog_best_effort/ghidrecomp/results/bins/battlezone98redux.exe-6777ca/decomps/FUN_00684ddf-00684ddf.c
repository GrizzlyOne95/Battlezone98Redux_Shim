
undefined4 FUN_00684ddf(void)

{
  char cVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (DAT_02b79b34 != 0) {
    cVar1 = FUN_0048efc0();
    if (cVar1 != '\0') {
      *(undefined4 *)(unaff_EBP + -0x1c) = 1;
      goto LAB_00684e1a;
    }
  }
  *(undefined4 *)(unaff_EBP + -0x1c) = 0;
LAB_00684e1a:
  *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x1c);
  if (*(int *)(unaff_EBP + -0x14) != 0) {
    FUN_00663aa0();
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + -0x14);
}

