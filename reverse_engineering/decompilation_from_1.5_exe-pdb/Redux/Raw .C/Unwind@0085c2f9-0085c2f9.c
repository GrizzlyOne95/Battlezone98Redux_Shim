
void Unwind_0085c2f9(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x8c) & 4) != 0) {
    *(uint *)(unaff_EBP + -0x8c) = *(uint *)(unaff_EBP + -0x8c) & 0xfffffffb;
    FUN_004180b0();
    return;
  }
  return;
}

