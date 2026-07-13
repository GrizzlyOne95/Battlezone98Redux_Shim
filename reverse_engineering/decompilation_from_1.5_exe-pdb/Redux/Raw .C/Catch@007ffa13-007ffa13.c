
undefined * Catch_007ffa13(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -0x24) = 0;
  ATL::COleDateTimeSpan::COleDateTimeSpan
            ((COleDateTimeSpan *)(unaff_EBP + -0x3c),*(long *)(unaff_EBP + 8),
             *(int *)(unaff_EBP + 0xc),*(int *)(unaff_EBP + -0x2c) + 0xc,
             *(int *)(unaff_EBP + -0x2c) + 0x14);
  FUN_00801190(unaff_EBP + -0x3c,*(undefined4 *)(unaff_EBP + 0x10),unaff_EBP + -0x24);
  *(undefined4 *)(unaff_EBP + -0x28) = *(undefined4 *)(unaff_EBP + -0x24);
  switch(*(undefined4 *)(unaff_EBP + -0x28)) {
  case 0:
    *(undefined1 *)(unaff_EBP + -0x14) = 0;
    return &LAB_007ffabc;
  case 1:
    return &DAT_007ffaae;
  case 2:
    *(undefined1 *)(unaff_EBP + -0x13) = 1;
    return &LAB_007ffaa0;
  case 3:
    FUN_008011e0(*(undefined4 *)(unaff_EBP + -0x2c));
  }
  return &DAT_007ffa97;
}

