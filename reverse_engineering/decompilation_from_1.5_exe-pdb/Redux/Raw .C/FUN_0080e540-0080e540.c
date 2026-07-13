
undefined4
FUN_0080e540(_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
             *param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  
  cVar1 = FID_conflict_operator__(param_2);
  if ((cVar1 == '\0') && (pcVar2 = (char *)get(), *pcVar2 == '.')) {
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++(param_1);
    return 1;
  }
  return 0;
}

