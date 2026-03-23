
void Unwind_0085c318(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x8c) & 8) != 0) {
    *(uint *)(unaff_EBP + -0x8c) = *(uint *)(unaff_EBP + -0x8c) & 0xfffffff7;
    FUN_004180b0();
    return;
  }
  return;
}

