
undefined4
FUN_0080faa0(char *param_1,char *param_2,undefined4 *param_3,undefined4 param_4,undefined1 *param_5)

{
  char cVar1;
  char *pcVar2;
  undefined4 local_8;
  
  local_8 = *param_3;
  while( true ) {
    if ((*param_1 == '\0') || (*param_2 == '\0')) {
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
                (param_3,&local_8,*param_5);
      *param_3 = local_8;
      return 1;
    }
    cVar1 = FID_conflict_operator__(param_4);
    if ((cVar1 != '\0') ||
       ((cVar1 = *param_1, pcVar2 = (char *)get(), cVar1 != *pcVar2 &&
        (cVar1 = *param_2, pcVar2 = (char *)get(), cVar1 != *pcVar2)))) break;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_8);
  }
  return 0;
}

