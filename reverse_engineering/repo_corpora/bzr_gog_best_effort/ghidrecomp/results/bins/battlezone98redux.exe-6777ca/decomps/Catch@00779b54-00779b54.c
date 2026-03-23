
undefined * Catch_00779b54(void)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar2;
  
  pcVar2 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x70) + 8))();
  FUN_0081e820("Renderer Ogre Exception:\n",uVar1);
  uVar1 = FUN_0081e660();
  uVar1 = FUN_004bc590(uVar1);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
  return &DAT_00779bf0;
}

