
char * __thiscall FUN_00766f30(_String_val<struct_std::_Simple_types<char>_> *param_1,uint param_2)

{
  char *pcVar1;
  
  if (*(uint *)(param_1 + 0x10) <= param_2) {
    FUN_00417440();
  }
  pcVar1 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
  return pcVar1 + param_2;
}

