
void __fastcall FUN_004235c0(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar1;
  char *pcVar2;
  
  pbVar1 = (basic_streambuf<char,struct_std::char_traits<char>_> *)
           std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
  if (pbVar1 != param_1 + 0x44) {
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
    *(char **)(param_1 + 0x38) = pcVar2;
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(param_1);
    *(char **)(param_1 + 0x3c) = pcVar2;
  }
  std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
            (param_1,(char *)(param_1 + 0x44),(char *)(param_1 + 0x44),(char *)(param_1 + 0x45));
  return;
}

