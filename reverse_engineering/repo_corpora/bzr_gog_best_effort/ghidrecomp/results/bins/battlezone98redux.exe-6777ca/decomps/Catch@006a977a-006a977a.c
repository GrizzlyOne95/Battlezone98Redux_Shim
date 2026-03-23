
undefined * Catch_006a977a(void)

{
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar2;
  int unaff_EBP;
  code *pcVar3;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (unaff_EBP == 0xd0) {
    uRam000000b8 = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x18) = unaff_EBP + -0xc0;
  }
  pcVar3 = FUN_004bc8c0;
  pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x18),"Failed to reset stats and achievements")
  ;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pcVar3);
  pbVar2 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pbVar2);
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_006a9808;
}

