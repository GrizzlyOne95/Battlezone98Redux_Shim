
undefined * Catch_All_0073b37f(void)

{
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 uVar1;
  int unaff_EBP;
  code *pcVar2;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 6;
  if (unaff_EBP == 0x298) {
    uRam00000234 = 0;
  }
  else {
    *(int *)(unaff_EBP + -100) = unaff_EBP + -0x288;
  }
  pcVar2 = FUN_004bc8c0;
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)
         FUN_004bc590(*(undefined4 *)(unaff_EBP + -100),
                      "cGogInterface::preinitGoGInterface, try/catch failure non-standard error!");
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
  uVar1 = GetPolicy(unaff_EBP + -0x2c);
  *(undefined4 *)(unaff_EBP + -0x84) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x80) = *(undefined4 *)(unaff_EBP + -0x84);
  *(undefined1 *)(unaff_EBP + -4) = 7;
  uVar1 = FUN_0041f870();
  FUN_007d6a70(uVar1);
  *(undefined1 *)(unaff_EBP + -4) = 6;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_0073b42c;
}

