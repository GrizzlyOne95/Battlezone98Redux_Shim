
undefined * Catch_007c7340(void)

{
  int iVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar3;
  
  iVar1 = FUN_007ae480(1);
  if (iVar1 == 0) {
    iVar1 = FUN_00434160();
    if (iVar1 != 9) {
      FUN_0081e1e0("Closing application due to complete render failure\n");
      FUN_00434170(9);
    }
    FUN_007c9170(1);
  }
  else {
    pcVar3 = FUN_004bc8c0;
    uVar2 = (**(code **)(**(int **)(unaff_EBP + -0x34) + 8))();
    FUN_0081e820("Ogre Rendering Exception Seen from UI: ",uVar2);
    uVar2 = FUN_0081e660();
    uVar2 = FUN_004bc590(uVar2);
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar3);
  }
  return &DAT_007c73c8;
}

