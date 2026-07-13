
int __fastcall FUN_006f5b70(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  return (int)pcVar1 - (int)pcVar2;
}

