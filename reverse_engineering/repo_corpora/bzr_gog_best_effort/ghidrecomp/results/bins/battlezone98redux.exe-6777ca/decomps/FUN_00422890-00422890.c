
int * __thiscall FUN_00422890(int *param_1,int param_2)

{
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar1;
  
  *param_1 = param_2;
  pbVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                     ((basic_ios<char,struct_std::char_traits<char>_> *)
                      (*param_1 + *(int *)(*(int *)*param_1 + 4)));
  if (pbVar1 != (basic_streambuf<char,struct_std::char_traits<char>_> *)0x0) {
    pbVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                       ((basic_ios<char,struct_std::char_traits<char>_> *)
                        (*param_1 + *(int *)(*(int *)*param_1 + 4)));
    (**(code **)(*(int *)pbVar1 + 4))();
  }
  return param_1;
}

