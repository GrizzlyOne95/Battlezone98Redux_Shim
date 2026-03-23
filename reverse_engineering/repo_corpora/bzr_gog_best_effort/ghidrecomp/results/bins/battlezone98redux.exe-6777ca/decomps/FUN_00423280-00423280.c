
void __thiscall
FUN_00423280(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,char **param_2,
            int param_3)

{
  param_1[0x4c] = (basic_streambuf<char,struct_std::char_traits<char>_>)(param_3 == 1);
  param_1[0x45] = (basic_streambuf<char,struct_std::char_traits<char>_>)0x0;
  std::basic_streambuf<char,struct_std::char_traits<char>_>::_Init(param_1);
  if (param_2 != (char **)0x0) {
    std::basic_streambuf<char,struct_std::char_traits<char>_>::_Init
              (param_1,param_2 + 2,param_2,(int *)(param_2 + 1),param_2 + 2,param_2,
               (int *)(param_2 + 1));
  }
  *(char ***)(param_1 + 0x50) = param_2;
  *(undefined4 *)(param_1 + 0x48) = DAT_02cc2b5c;
  *(undefined4 *)(param_1 + 0x40) = 0;
  return;
}

