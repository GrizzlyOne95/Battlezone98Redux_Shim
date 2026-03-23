
void Unwind_008656e8(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x60) & 2) != 0) {
    *(uint *)(unaff_EBP + -0x60) = *(uint *)(unaff_EBP + -0x60) & 0xfffffffd;
    FUN_004180b0();
    return;
  }
  return;
}

