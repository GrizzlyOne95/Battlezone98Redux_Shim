
void Unwind_00862183(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x244) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x244) = *(uint *)(unaff_EBP + -0x244) & 0xfffffffe;
    FUN_00482800();
    return;
  }
  return;
}

