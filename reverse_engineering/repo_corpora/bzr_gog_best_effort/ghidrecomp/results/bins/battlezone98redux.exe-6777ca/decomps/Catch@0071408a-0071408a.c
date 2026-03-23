
undefined * Catch_0071408a(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = basic_string<>("error in handle_read_http_response: ");
  *(undefined4 *)(unaff_EBP + -0x16c) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x150) = *(undefined4 *)(unaff_EBP + -0x16c);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x148) + 4))();
  uVar1 = FUN_0045f170(unaff_EBP + -0x4c,*(undefined4 *)(unaff_EBP + -0x150),uVar1);
  *(undefined4 *)(unaff_EBP + -0x158) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x160) = *(undefined4 *)(unaff_EBP + -0x158);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  FUN_006d46a0(0x10,*(undefined4 *)(unaff_EBP + -0x160));
  *(undefined1 *)(unaff_EBP + -4) = 3;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 2;
  ~basic_string<>();
  uVar1 = make_error_code(unaff_EBP + -0x1c8,1);
  FUN_006daf10(uVar1);
  return &DAT_0071414e;
}

