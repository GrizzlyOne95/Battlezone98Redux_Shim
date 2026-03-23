
undefined * Catch_00684d9b(void)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar2;
  
  pcVar2 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x20) + 8))();
  FUN_0081e820("Ogre Rendering Exception Seen from restore context: ",uVar1);
  uVar1 = FUN_0081e660();
  uVar1 = FUN_004bc590(uVar1);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
  return &DAT_00684de8;
}

