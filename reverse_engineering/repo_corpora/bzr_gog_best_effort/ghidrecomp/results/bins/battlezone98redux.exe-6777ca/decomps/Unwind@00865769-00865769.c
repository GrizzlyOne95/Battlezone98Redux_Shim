
void Unwind_00865769(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x48) & 2) != 0) {
    *(uint *)(unaff_EBP + -0x48) = *(uint *)(unaff_EBP + -0x48) & 0xfffffffd;
    FUN_004180b0();
    return;
  }
  return;
}

