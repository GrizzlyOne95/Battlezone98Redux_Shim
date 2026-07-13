
undefined * Catch_0073b511(void)

{
  undefined4 uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int unaff_EBP;
  code *pcVar4;
  
  FUN_00574400(3,1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (unaff_EBP == 0xf8) {
    uRam000000c0 = 0;
  }
  else {
    *(int *)(unaff_EBP + -0x38) = unaff_EBP + -0xe8;
  }
  pcVar4 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x30) + 8))();
  iVar2 = (**(code **)(**(int **)(unaff_EBP + -0x30) + 0xc))(&DAT_0089a17c,uVar1);
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x30) + 4))(&DAT_0089a17c);
  uVar1 = FUN_004bc590(*(undefined4 *)(unaff_EBP + -0x38),"GoG Sign In try/catch failure error no: "
                       ,uVar1);
  uVar1 = FUN_004bc590(uVar1);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar2);
  uVar1 = FUN_004bc590(pbVar3);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
  uVar1 = GetPolicy(unaff_EBP + -0x2c);
  *(undefined4 *)(unaff_EBP + -0x48) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x40) = *(undefined4 *)(unaff_EBP + -0x48);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  uVar1 = FUN_0041f870();
  FUN_007d6a70(uVar1);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_00417f10();
  return &DAT_0073b618;
}

