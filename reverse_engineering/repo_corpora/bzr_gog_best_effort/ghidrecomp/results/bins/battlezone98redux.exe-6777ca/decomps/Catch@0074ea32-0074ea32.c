
undefined * Catch_0074ea32(void)

{
  undefined4 uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  int unaff_EBP;
  code *pcVar5;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (unaff_EBP == 0x1a0) {
    uRam0000017c = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x24) = unaff_EBP + -400;
  }
  pcVar5 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x18) + 8))();
  iVar2 = (**(code **)(**(int **)(unaff_EBP + -0x18) + 0xc))(&DAT_0089a17c,uVar1);
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x18) + 4))(&DAT_0089a17c);
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x24),
                       "CGalaxyLobby::GetLobbyList, try / catch failure error no : ",uVar1);
  uVar1 = FUN_004bc590(uVar1);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar2);
  uVar1 = FUN_004bc590(pbVar3);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  FUN_00417f10();
  return &DAT_0074eb20;
}

