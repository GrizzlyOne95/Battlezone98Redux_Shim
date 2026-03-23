
undefined4 * __thiscall
FUN_00806540(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            int *param_5)

{
  char cVar1;
  char *pcVar2;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *p_Var3;
  undefined4 local_10;
  undefined4 local_c;
  char local_5;
  
  *param_5 = 1;
  local_c = param_3;
  local_10 = param_3;
  while (cVar1 = FID_conflict_operator__(&param_4), cVar1 != '\0') {
    local_5 = '\0';
    cVar1 = FID_conflict_operator__(&param_4);
    if ((cVar1 != '\0') && (pcVar2 = (char *)get(param_1), *pcVar2 == '\r')) {
      local_5 = '\x01';
      p_Var3 = std::
               _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
               operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_c);
      local_10 = *(undefined4 *)p_Var3;
    }
    cVar1 = FID_conflict_operator__(&param_4);
    if ((cVar1 != '\0') && (pcVar2 = (char *)get(), *pcVar2 == '\n')) {
      local_5 = '\x01';
      p_Var3 = std::
               _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
               operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_c);
      local_10 = *(undefined4 *)p_Var3;
    }
    if (local_5 == '\0') {
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&local_c);
    }
    else {
      *param_5 = *param_5 + 1;
    }
  }
  *param_2 = local_10;
  return param_2;
}

