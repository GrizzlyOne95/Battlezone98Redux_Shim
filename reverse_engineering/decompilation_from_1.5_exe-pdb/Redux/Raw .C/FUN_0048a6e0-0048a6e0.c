
undefined4 * __thiscall FUN_0048a6e0(undefined4 *param_1,int *param_2)

{
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar1;
  
  pbVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                     ((basic_ios<char,struct_std::char_traits<char>_> *)
                      ((int)param_2 + *(int *)(*param_2 + 4)));
  *param_1 = pbVar1;
  pbVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                     ((basic_ios<char,struct_std::char_traits<char>_> *)
                      ((int)param_2 + *(int *)(*param_2 + 4)));
  *(bool *)(param_1 + 1) = pbVar1 == (basic_streambuf<char,struct_std::char_traits<char>_> *)0x0;
  return param_1;
}

