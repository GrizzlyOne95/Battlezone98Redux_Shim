
undefined1 * __thiscall FUN_006e27b0(undefined1 *param_1,int *param_2)

{
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar1;
  
  *param_1 = 0;
  pbVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                     ((basic_ios<char,struct_std::char_traits<char>_> *)
                      ((int)param_2 + *(int *)(*param_2 + 4)));
  *(basic_streambuf<char,struct_std::char_traits<char>_> **)(param_1 + 4) = pbVar1;
  return param_1;
}

