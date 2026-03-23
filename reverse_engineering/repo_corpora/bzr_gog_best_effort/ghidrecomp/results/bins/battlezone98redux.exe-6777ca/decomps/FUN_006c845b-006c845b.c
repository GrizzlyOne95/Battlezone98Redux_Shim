
void FUN_006c845b(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(char *)(unaff_EBP + -0x45) != '\0') {
    FUN_006c6df0();
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

