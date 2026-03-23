
void Unwind_00864bf6(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x100) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x100) = *(uint *)(unaff_EBP + -0x100) & 0xfffffffe;
    FUN_00800170();
    return;
  }
  return;
}

