
void FUN_006be8c5(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if ((0x2000 < *(int *)(unaff_EBP + -0x78)) && (*(char *)(unaff_EBP + -0x69) == '\0')) {
    *(undefined4 *)(unaff_EBP + -4) = 2;
    FUN_00447eb0(*(undefined4 *)(unaff_EBP + -0x78));
    FUN_006db800(unaff_EBP + -0x7c);
    *(undefined1 *)(unaff_EBP + -0x69) = 1;
    FUN_006be8c5();
    return;
  }
  FUN_007d6a70("BZRNet P2P Socket Opened With %ld received buffer, %ld send buffer, port %ld\n",
               *(undefined4 *)(unaff_EBP + -0x70),*(undefined4 *)(unaff_EBP + -0x78),DAT_00945704);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

