
undefined * Catch_0073b1c6(void)

{
  undefined4 uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int unaff_EBP;
  code *pcVar4;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (unaff_EBP == 0x138) {
    uRam000000d0 = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x68) = unaff_EBP + -0x128;
  }
  pcVar4 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x60) + 8))();
  iVar2 = (**(code **)(**(int **)(unaff_EBP + -0x60) + 0xc))(&DAT_0089a17c,uVar1);
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x60) + 4))(&DAT_0089a17c);
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x68),
                       "cGogInterface::preinitGoGInterface, try/catch failure error no: ",uVar1);
  uVar1 = FUN_004bc590(uVar1);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar2);
  uVar1 = FUN_004bc590(pbVar3);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
  uVar1 = GetPolicy(unaff_EBP + -0x44);
  *(undefined4 *)(unaff_EBP + -0x78) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x88) = *(undefined4 *)(unaff_EBP + -0x78);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  uVar1 = FUN_0041f870();
  FUN_007d6a70(uVar1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_0073b442;
}

