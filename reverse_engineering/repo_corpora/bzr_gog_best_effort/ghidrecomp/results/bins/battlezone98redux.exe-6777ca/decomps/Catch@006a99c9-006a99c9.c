
undefined * Catch_006a99c9(void)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  int unaff_EBP;
  code *pcVar4;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (unaff_EBP == 0xd4) {
    uRam000000bc = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x18) = unaff_EBP + -0xc4;
  }
  pcVar4 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x20) + 8))();
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x18),
                       "Stats()->StoreStatsAndAchievements, error=",uVar1);
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar4);
  pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_006a9a6e;
}

