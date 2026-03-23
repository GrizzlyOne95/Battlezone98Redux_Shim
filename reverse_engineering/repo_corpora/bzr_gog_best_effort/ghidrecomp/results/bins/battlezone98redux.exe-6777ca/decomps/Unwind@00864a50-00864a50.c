
void Unwind_00864a50(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x60) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x60) = *(uint *)(unaff_EBP + -0x60) & 0xfffffffe;
    FUN_00800170();
    return;
  }
  return;
}

