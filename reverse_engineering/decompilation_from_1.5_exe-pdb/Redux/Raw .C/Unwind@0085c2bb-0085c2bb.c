
void Unwind_0085c2bb(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x8c) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x8c) = *(uint *)(unaff_EBP + -0x8c) & 0xfffffffe;
    FUN_004180b0();
    return;
  }
  return;
}

