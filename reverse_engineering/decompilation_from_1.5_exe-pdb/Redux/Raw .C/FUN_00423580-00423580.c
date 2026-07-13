
void __fastcall FUN_00423580(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar1;
  
  pbVar1 = (basic_streambuf<char,struct_std::char_traits<char>_> *)
           std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
  if (pbVar1 == param_1 + 0x44) {
    std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
              (param_1,*(char **)(param_1 + 0x38),*(char **)(param_1 + 0x38),
               *(char **)(param_1 + 0x3c));
  }
  return;
}

