
void Unwind_00850e7e(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x180) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x180) = *(uint *)(unaff_EBP + -0x180) & 0xfffffffe;
    ~basic_string<>();
    return;
  }
  return;
}

