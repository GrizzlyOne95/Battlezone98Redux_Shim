
undefined4
FUN_0080e5f0(_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
             *param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    pcVar2 = (char *)get();
    if (*pcVar2 != 'e') {
      pcVar2 = (char *)get();
      if (*pcVar2 != 'E') goto LAB_0080e626;
    }
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++(param_1);
    uVar3 = 1;
  }
  else {
LAB_0080e626:
    uVar3 = 0;
  }
  return uVar3;
}

