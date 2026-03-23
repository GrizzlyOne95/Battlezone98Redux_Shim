
undefined4 FUN_0080a090(char *param_1,undefined4 *param_2,undefined4 param_3,undefined1 *param_4)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  undefined4 local_c;
  char local_5;
  
  local_c = *param_2;
  local_5 = *param_1;
  while( true ) {
    if (local_5 == '\0') {
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
                (param_2,&local_c,*param_4);
      *param_2 = local_c;
      return 1;
    }
    cVar2 = FID_conflict_operator__(param_3);
    cVar1 = local_5;
    if ((cVar2 != '\0') || (pcVar3 = (char *)get(), cVar1 != *pcVar3)) break;
    param_1 = param_1 + 1;
    local_5 = *param_1;
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
  }
  return 0;
}

