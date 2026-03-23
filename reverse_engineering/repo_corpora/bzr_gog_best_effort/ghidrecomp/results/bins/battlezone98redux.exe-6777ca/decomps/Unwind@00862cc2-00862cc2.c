
void Unwind_00862cc2(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x9c) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x9c) = *(uint *)(unaff_EBP + -0x9c) & 0xfffffffe;
    FUN_004499a0();
    return;
  }
  return;
}

