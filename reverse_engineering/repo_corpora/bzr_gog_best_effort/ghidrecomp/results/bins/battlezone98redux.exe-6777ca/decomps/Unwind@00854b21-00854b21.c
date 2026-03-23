
void Unwind_00854b21(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x104) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x104) = *(uint *)(unaff_EBP + -0x104) & 0xfffffffe;
    ~basic_string<>();
    return;
  }
  return;
}

