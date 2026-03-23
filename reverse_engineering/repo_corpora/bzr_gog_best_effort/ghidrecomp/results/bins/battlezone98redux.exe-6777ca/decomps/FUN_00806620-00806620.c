
int FUN_00806620(undefined4 param_1)

{
  char cVar1;
  undefined4 local_c;
  int local_8;
  
  local_8 = 1;
  local_c = param_1;
  while( true ) {
    cVar1 = FID_conflict_operator__(&stack0x00000008);
    if (cVar1 == '\0') break;
    local_8 = local_8 + 1;
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
  }
  return local_8;
}

