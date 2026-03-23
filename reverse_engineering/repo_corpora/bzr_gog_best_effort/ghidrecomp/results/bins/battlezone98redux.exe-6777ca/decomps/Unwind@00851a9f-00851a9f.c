
void Unwind_00851a9f(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x8ac) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x8ac) = *(uint *)(unaff_EBP + -0x8ac) & 0xfffffffe;
    ~basic_string<>();
    return;
  }
  return;
}

