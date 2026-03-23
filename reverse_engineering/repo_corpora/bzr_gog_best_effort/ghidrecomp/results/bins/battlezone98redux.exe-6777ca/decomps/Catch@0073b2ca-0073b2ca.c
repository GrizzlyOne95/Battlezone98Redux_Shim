
undefined * Catch_0073b2ca(void)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar2;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  if (unaff_EBP == 0x1e8) {
    uRam0000017c = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x6c) = unaff_EBP + -0x1d8;
  }
  pcVar2 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x74) + 4))();
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x6c),
                       "cGogInterface::preinitGoGInterface, try/catch failure std error: ",uVar1);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
  uVar1 = GetPolicy(unaff_EBP + -0x5c);
  *(undefined4 *)(unaff_EBP + -0x7c) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x70) = *(undefined4 *)(unaff_EBP + -0x7c);
  *(undefined1 *)(unaff_EBP + -4) = 5;
  uVar1 = FUN_0041f870();
  FUN_007d6a70(uVar1);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_0073b437;
}

