
undefined4 FUN_00806670(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_8;
  
  uVar4 = 0;
  local_8 = param_2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&stack0x0000000c);
    if (cVar1 == '\0') break;
    uVar3 = extraout_var;
    pcVar2 = (char *)get(extraout_var,uVar4);
    if (*pcVar2 == '\r') break;
    pcVar2 = (char *)get(uVar3,uVar4);
    if (*pcVar2 == '\n') break;
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_8);
  }
  FUN_006c8830(param_2,local_8);
  return param_1;
}

