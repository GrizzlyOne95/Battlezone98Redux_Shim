
void Unwind_00860900(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0xd8) & 1) != 0) {
    *(uint *)(unaff_EBP + -0xd8) = *(uint *)(unaff_EBP + -0xd8) & 0xfffffffe;
    ~basic_string<>();
    return;
  }
  return;
}

