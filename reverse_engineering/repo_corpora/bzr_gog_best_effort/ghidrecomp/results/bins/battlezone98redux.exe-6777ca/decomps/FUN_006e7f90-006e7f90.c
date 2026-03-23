
undefined4 * FUN_006e7f90(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  local_8 = param_2;
  iVar2 = std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator-((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                     *)&param_3,
                    (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                     *)&param_2);
  if (2 < iVar2) {
    pcVar3 = (char *)get();
    if (*pcVar3 == '\r') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
      operator+((iterator *)&param_2,(int)local_c);
      pcVar3 = (char *)get();
      if (*pcVar3 == '\n') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator
        ::operator+((iterator *)&param_2,(int)local_10);
        puVar4 = (undefined1 *)get();
        cVar1 = FUN_006b6850(*puVar4);
        if (cVar1 != '\0') {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          iterator::operator+=((iterator *)&local_8,3);
        }
      }
    }
  }
  puVar5 = (undefined4 *)FUN_006d9b70(local_14,local_8,param_3,FUN_006b6880);
  *param_1 = *puVar5;
  return param_1;
}

