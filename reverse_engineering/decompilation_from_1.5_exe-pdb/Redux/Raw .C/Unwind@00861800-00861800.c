
void Unwind_00861800(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x68) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x68) = *(uint *)(unaff_EBP + -0x68) & 0xfffffffe;
    FUN_00667660();
    return;
  }
  return;
}

