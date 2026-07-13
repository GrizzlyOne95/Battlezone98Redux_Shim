
void Unwind_00865701(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x60) & 4) != 0) {
    *(uint *)(unaff_EBP + -0x60) = *(uint *)(unaff_EBP + -0x60) & 0xfffffffb;
    FUN_004180b0();
    return;
  }
  return;
}

