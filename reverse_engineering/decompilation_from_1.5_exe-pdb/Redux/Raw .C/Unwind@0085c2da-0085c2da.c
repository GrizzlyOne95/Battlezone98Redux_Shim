
void Unwind_0085c2da(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x8c) & 2) != 0) {
    *(uint *)(unaff_EBP + -0x8c) = *(uint *)(unaff_EBP + -0x8c) & 0xfffffffd;
    FUN_004180b0();
    return;
  }
  return;
}

