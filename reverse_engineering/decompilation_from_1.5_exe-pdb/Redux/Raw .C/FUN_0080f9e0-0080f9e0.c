
bool FUN_0080f9e0(_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *param_1)

{
  char *pcVar1;
  bool bVar2;
  
  pcVar1 = (char *)get();
  bVar2 = *pcVar1 == '-';
  if ((bVar2) || (pcVar1 = (char *)get(), *pcVar1 == '+')) {
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++(param_1);
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

