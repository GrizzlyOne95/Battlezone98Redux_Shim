
void Unwind_008622fe(void)

{
  int unaff_EBP;
  
  if ((*(uint *)(unaff_EBP + -0x244) & 2) != 0) {
    *(uint *)(unaff_EBP + -0x244) = *(uint *)(unaff_EBP + -0x244) & 0xfffffffd;
    FUN_00482800();
    return;
  }
  return;
}

