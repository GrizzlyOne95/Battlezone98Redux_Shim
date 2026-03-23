
void __fastcall FUN_00420f50(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  *(undefined ***)param_1 = std::basic_filebuf<char,struct_std::char_traits<char>_>::vftable;
  if (*(int *)(param_1 + 0x50) != 0) {
    FUN_00423580();
  }
  if (param_1[0x4c] != (basic_streambuf<char,struct_std::char_traits<char>_>)0x0) {
    FUN_00423210();
  }
  std::basic_streambuf<char,struct_std::char_traits<char>_>::
  ~basic_streambuf<char,struct_std::char_traits<char>_>(param_1);
  return;
}

