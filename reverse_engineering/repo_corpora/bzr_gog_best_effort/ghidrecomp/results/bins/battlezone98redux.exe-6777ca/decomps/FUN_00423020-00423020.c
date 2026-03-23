
void __fastcall FUN_00423020(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char *pcVar1;
  int iVar2;
  char *local_c;
  
  if ((*(uint *)(param_1 + 0x3c) & 1) != 0) {
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
    if (pcVar1 == (char *)0x0) {
      local_c = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(param_1);
    }
    else {
      local_c = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(param_1);
    }
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
    iVar2 = (int)local_c - (int)pcVar1;
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
    FUN_00417180(pcVar1,iVar2);
  }
  std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
            (param_1,(char *)0x0,(char *)0x0,(char *)0x0);
  std::basic_streambuf<char,struct_std::char_traits<char>_>::setp(param_1,(char *)0x0,(char *)0x0);
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffe;
  return;
}

