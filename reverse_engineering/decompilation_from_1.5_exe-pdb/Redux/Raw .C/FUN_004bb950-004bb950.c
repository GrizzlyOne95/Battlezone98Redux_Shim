
int __thiscall FUN_004bb950(int param_1,basic_ostream<char,struct_std::char_traits<char>_> *param_2)

{
  bool bVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845178;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00422890(param_2);
  local_8 = 0;
  bVar1 = std::ios_base::good((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4)));
  if (bVar1) {
    pbVar2 = std::basic_ios<char,struct_std::char_traits<char>_>::tie
                       ((basic_ios<char,struct_std::char_traits<char>_> *)
                        (param_2 + *(int *)(*(int *)param_2 + 4)));
    if (pbVar2 != (basic_ostream<char,struct_std::char_traits<char>_> *)0x0) {
      pbVar2 = std::basic_ios<char,struct_std::char_traits<char>_>::tie
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          (param_2 + *(int *)(*(int *)param_2 + 4)));
      if (pbVar2 != param_2) {
        pbVar2 = std::basic_ios<char,struct_std::char_traits<char>_>::tie
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            (param_2 + *(int *)(*(int *)param_2 + 4)));
        std::basic_ostream<char,struct_std::char_traits<char>_>::flush(pbVar2);
      }
    }
  }
  bVar1 = std::ios_base::good((ios_base *)(param_2 + *(int *)(*(int *)param_2 + 4)));
  *(bool *)(param_1 + 4) = bVar1;
  ExceptionList = local_10;
  return param_1;
}

