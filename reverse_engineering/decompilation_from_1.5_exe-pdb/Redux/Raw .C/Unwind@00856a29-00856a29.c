
void Unwind_00856a29(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x90) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x90) = *(uint *)(unaff_EBP + -0x90) & 0xfffffffe;
    ~basic_string<>();
    return;
  }
  return;
}

