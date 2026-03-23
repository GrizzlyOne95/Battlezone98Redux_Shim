
void __thiscall
FUN_00423540(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,codecvt_base *param_2)

{
  bool bVar1;
  
  bVar1 = std::codecvt_base::always_noconv(param_2);
  if (bVar1) {
    *(undefined4 *)(param_1 + 0x40) = 0;
  }
  else {
    *(codecvt_base **)(param_1 + 0x40) = param_2;
    std::basic_streambuf<char,struct_std::char_traits<char>_>::_Init(param_1);
  }
  return;
}

