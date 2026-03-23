
void Unwind_00865c8e(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xd4) & 4) != 0) {
    *(uint *)(unaff_EBP + -0xd4) = *(uint *)(unaff_EBP + -0xd4) & 0xfffffffb;
    FUN_004180b0();
    return;
  }
  return;
}

