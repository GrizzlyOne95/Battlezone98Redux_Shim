
undefined ** Catch_00778fe7(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar3;
  
  FUN_0077c670();
  cVar1 = FUN_00777710();
  if (cVar1 != '\0') {
    *(undefined1 *)
     (*(int *)(unaff_EBP + -0x24) + 0x270 + *(int *)(unaff_EBP + 0xc) * 4 +
     *(int *)(unaff_EBP + 0x10)) = 1;
  }
  pcVar3 = FUN_004bc8c0;
  uVar2 = (**(code **)(**(int **)(unaff_EBP + -0xa0) + 4))();
  FUN_0081e820("Renderer Std Exception: ",uVar2);
  uVar2 = FUN_0081e660();
  uVar2 = FUN_004bc590(uVar2);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar3);
  return &PTR_DAT_00779061;
}

