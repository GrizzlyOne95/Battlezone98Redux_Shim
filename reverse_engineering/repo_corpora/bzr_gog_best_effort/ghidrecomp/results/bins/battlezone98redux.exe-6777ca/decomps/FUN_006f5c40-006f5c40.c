
void __thiscall
FUN_006f5c40(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,int param_2)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(param_1);
  if (pcVar2 < pcVar1 + param_2) {
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(param_1);
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
    param_2 = (int)pcVar1 - (int)pcVar2;
  }
  std::basic_streambuf<char,struct_std::char_traits<char>_>::pbump(param_1,param_2);
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
  std::basic_streambuf<char,struct_std::char_traits<char>_>::setg(param_1,pcVar3,pcVar2,pcVar1);
  return;
}

