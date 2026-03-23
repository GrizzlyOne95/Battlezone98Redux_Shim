
bool __thiscall
FUN_0080f4e0(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined1 *param_5)

{
  char cVar1;
  char *pcVar2;
  undefined4 local_c;
  char local_5;
  
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_2,param_3,*param_5,param_1);
  local_c = *param_2;
  local_5 = '\0';
  cVar1 = FID_conflict_operator__(param_3);
  if ((cVar1 != '\0') && (pcVar2 = (char *)get(), *pcVar2 == '\r')) {
    local_5 = '\x01';
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
  }
  cVar1 = FID_conflict_operator__(param_3);
  if ((cVar1 != '\0') && (pcVar2 = (char *)get(), *pcVar2 == '\n')) {
    local_5 = '\x01';
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
  }
  if (local_5 != '\0') {
    *param_2 = local_c;
  }
  return local_5 != '\0';
}

