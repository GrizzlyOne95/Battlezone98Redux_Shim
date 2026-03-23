
basic_istream<char,struct_std::char_traits<char>_> *
FUN_0073abd0(basic_istream<char,struct_std::char_traits<char>_> *param_1)

{
  bool bVar1;
  int local_20;
  int local_1c;
  int *local_18;
  basic_istream<char,struct_std::char_traits<char>_> *local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_14 = std::basic_istream<char,struct_std::char_traits<char>_>::get(param_1,&local_5);
  bVar1 = std::ios_base::operator!((ios_base *)(local_14 + *(int *)(*(int *)local_14 + 4)));
  if (!bVar1) {
    local_10 = local_5 + -0x42;
    switch(local_5) {
    case 'B':
      local_c = 3;
      break;
    default:
      std::basic_istream<char,struct_std::char_traits<char>_>::putback(param_1,local_5);
      std::basic_ios<char,struct_std::char_traits<char>_>::setstate
                ((basic_ios<char,struct_std::char_traits<char>_> *)
                 (param_1 + *(int *)(*(int *)param_1 + 4)),2,false);
      return param_1;
    case 'G':
      local_c = 2;
      break;
    case 'I':
      local_c = 0;
      break;
    case 'S':
      local_c = 1;
    }
    std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
              (param_1,(__uint64 *)&local_20);
    bVar1 = std::ios_base::operator_bool((ios_base *)(param_1 + *(int *)(*(int *)param_1 + 4)));
    if ((bVar1) && ((local_20 == 0 && local_1c == 0 || (local_c != 0)))) {
      *local_18 = local_c;
      local_18[2] = local_20;
      local_18[3] = local_1c;
    }
    else {
      std::basic_ios<char,struct_std::char_traits<char>_>::setstate
                ((basic_ios<char,struct_std::char_traits<char>_> *)
                 (param_1 + *(int *)(*(int *)param_1 + 4)),2,false);
    }
  }
  return param_1;
}

