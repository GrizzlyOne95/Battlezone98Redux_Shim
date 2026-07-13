
void Unwind_008615f6(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x48) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x48) = *(uint *)(unaff_EBP + -0x48) & 0xfffffffe;
    FUN_006c3560();
    return;
  }
  return;
}

