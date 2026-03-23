
undefined * Catch_00755323(void)

{
  undefined4 uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  int unaff_EBP;
  code *pcVar5;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 5;
  if (unaff_EBP == 0x204) {
    uRam000001b0 = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x54) = unaff_EBP + -500;
  }
  pcVar5 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x48) + 8))();
  iVar2 = (**(code **)(**(int **)(unaff_EBP + -0x48) + 0xc))(&DAT_0089a17c,uVar1);
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x48) + 4))(&DAT_0089a17c);
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x54),
                       "cNetFriendsGog::InviteFriendById, try/catch failure error no: ",uVar1);
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
  *(undefined1 *)(unaff_EBP + -4) = 4;
  FUN_00417f10();
  return &DAT_00755411;
}

