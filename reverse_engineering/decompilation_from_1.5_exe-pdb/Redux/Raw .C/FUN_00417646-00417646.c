
void FUN_00417646(void)

{
  char *pcVar1;
  int unaff_EBP;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + 0xc) != 0) {
    uVar3 = *(uint *)(unaff_EBP + 0xc);
    pcVar1 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                       (*(_String_val<struct_std::_Simple_types<char>_> **)(unaff_EBP + -0x18));
    std::char_traits<char>::copy(*(char **)(unaff_EBP + -0x20),pcVar1,uVar3);
  }
  FID_conflict__Tidy(1,0);
  iVar4 = unaff_EBP + -0x20;
  uVar2 = *(undefined4 *)(unaff_EBP + -0x18);
  Getal(unaff_EBP + -0x13);
  construct<>(uVar2,iVar4);
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 0x14) = *(undefined4 *)(unaff_EBP + -0x1c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
            (*(basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
               **)(unaff_EBP + -0x18),*(uint *)(unaff_EBP + 0xc));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

