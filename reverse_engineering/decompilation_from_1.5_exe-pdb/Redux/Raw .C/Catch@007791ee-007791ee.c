
undefined * Catch_007791ee(void)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int unaff_EBP;
  code *pcVar2;
  
  *(undefined1 *)
   (*(int *)(unaff_EBP + -0x24) + 0x270 + *(int *)(unaff_EBP + 0xc) * 4 + *(int *)(unaff_EBP + 0x10)
   ) = 1;
  pcVar2 = FUN_004bc8c0;
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x9c) + 4))();
  FUN_0081e820("Renderer Std Exception: ",uVar1);
  uVar1 = FUN_0081e660();
  uVar1 = FUN_004bc590(uVar1);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar2);
  return &DAT_00779255;
}

