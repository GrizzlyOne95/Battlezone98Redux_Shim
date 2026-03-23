
void Unwind_00865cd2(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xd4) & 0x10) != 0) {
    *(uint *)(unaff_EBP + -0xd4) = *(uint *)(unaff_EBP + -0xd4) & 0xffffffef;
    FUN_004180b0();
    return;
  }
  return;
}

