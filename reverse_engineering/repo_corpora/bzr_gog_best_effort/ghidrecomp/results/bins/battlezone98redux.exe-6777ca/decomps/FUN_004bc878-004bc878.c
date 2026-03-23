
undefined4 FUN_004bc878(void)

{
  int unaff_EBP;
  
  std::basic_ios<char,struct_std::char_traits<char>_>::setstate
            ((basic_ios<char,struct_std::char_traits<char>_> *)
             (*(int *)(unaff_EBP + 8) + *(int *)(**(int **)(unaff_EBP + 8) + 4)),
             *(int *)(unaff_EBP + -0x18),false);
  *(undefined4 *)(unaff_EBP + -0x44) = *(undefined4 *)(unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  FUN_004bba20();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + -0x44);
}

