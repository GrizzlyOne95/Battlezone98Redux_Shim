
undefined * Catch_006e90e6(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = basic_string<>("termination_handler call failed. Reason was: ");
  *(undefined4 *)(unaff_EBP + -0x5c) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x4c) = *(undefined4 *)(unaff_EBP + -0x5c);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x54) + 4))();
  uVar1 = FUN_0045f170(unaff_EBP + -0x44,*(undefined4 *)(unaff_EBP + -0x4c),uVar1);
  *(undefined4 *)(unaff_EBP + -0x58) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x50) = *(undefined4 *)(unaff_EBP + -0x58);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  FUN_006d46a0(8,*(undefined4 *)(unaff_EBP + -0x50));
  *(undefined1 *)(unaff_EBP + -4) = 2;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 1;
  ~basic_string<>();
  return &DAT_006e9166;
}

