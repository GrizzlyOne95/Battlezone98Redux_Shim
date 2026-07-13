
undefined1 FUN_0041c520(basic_istream<char,struct_std::char_traits<char>_> *param_1,int *param_2)

{
  undefined1 uVar1;
  bool bVar2;
  char local_5;
  
  std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(param_1,param_2);
  local_5 = '\0';
  std::basic_istream<char,struct_std::char_traits<char>_>::get(param_1,&local_5);
  bVar2 = std::ios_base::operator_bool((ios_base *)(param_1 + *(int *)(*(int *)param_1 + 4)));
  if ((bVar2) && (local_5 == ';')) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

