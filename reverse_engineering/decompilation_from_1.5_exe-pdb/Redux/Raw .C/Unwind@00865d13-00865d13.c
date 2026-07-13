
void Unwind_00865d13(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xd4) & 0x40) != 0) {
    *(uint *)(unaff_EBP + -0xd4) = *(uint *)(unaff_EBP + -0xd4) & 0xffffffbf;
    FUN_004180b0();
    return;
  }
  return;
}

