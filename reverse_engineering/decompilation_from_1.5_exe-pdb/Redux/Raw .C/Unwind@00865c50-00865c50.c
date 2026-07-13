
void Unwind_00865c50(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xd4) & 1) != 0) {
    *(uint *)(unaff_EBP + -0xd4) = *(uint *)(unaff_EBP + -0xd4) & 0xfffffffe;
    FUN_004180b0();
    return;
  }
  return;
}

