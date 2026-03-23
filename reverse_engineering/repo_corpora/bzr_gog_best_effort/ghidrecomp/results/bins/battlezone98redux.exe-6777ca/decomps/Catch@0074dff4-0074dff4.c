
undefined * Catch_0074dff4(void)

{
  undefined4 uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  int unaff_EBP;
  code *pcVar5;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (unaff_EBP == 0xdc) {
    uRam000000c0 = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x1c) = unaff_EBP + -0xcc;
  }
  pcVar5 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x14) + 8))();
  iVar2 = (**(code **)(**(int **)(unaff_EBP + -0x14) + 0xc))(&DAT_0089a17c,uVar1);
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x14) + 4))(&DAT_0089a17c);
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x1c),
                       "CGalaxyLobby::GetMyExtID, try/catch failure error no: ",uVar1);
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
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_0074e0e2;
}

