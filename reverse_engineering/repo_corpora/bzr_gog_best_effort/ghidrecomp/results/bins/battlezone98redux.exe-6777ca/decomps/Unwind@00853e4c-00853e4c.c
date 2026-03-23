
void Unwind_00853e4c(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x10) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x10) = *(uint *)(unaff_EBP + -0x10) & 0xfffffffe;
                    /* WARNING: Could not recover jumptable at 0x00853e5f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    std::_Locinfo::~_Locinfo((_Locinfo *)(unaff_EBP + -0x58));
    return;
  }
  return;
}

