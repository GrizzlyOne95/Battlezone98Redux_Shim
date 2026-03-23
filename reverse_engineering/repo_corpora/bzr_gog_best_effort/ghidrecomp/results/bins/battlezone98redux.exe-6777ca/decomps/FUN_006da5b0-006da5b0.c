
undefined4 __thiscall FUN_006da5b0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 local_8;
  
  local_8 = param_2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&stack0x00000008);
    if (cVar1 == '\0') {
      return 1;
    }
    puVar2 = (undefined1 *)get();
    iVar3 = FUN_006bb930(param_1,param_1 + 4,*puVar2);
    if (iVar3 == 1) break;
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_8);
  }
  return 0;
}

