
int __thiscall
FUN_0048a770(_String_val<struct_std::_Simple_types<char>_> *param_1,undefined4 param_2,uint param_3,
            int param_4)

{
  int iVar1;
  char *pcVar2;
  uint local_10;
  char *local_c;
  
  if ((param_4 == 0) || (*(int *)(param_1 + 0x10) == 0)) {
LAB_0048a7fc:
    iVar1 = -1;
  }
  else {
    if (param_3 < *(uint *)(param_1 + 0x10)) {
      local_10 = param_3;
    }
    else {
      local_10 = *(int *)(param_1 + 0x10) - 1;
    }
    local_c = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
    local_c = local_c + local_10;
    while (iVar1 = FUN_00482540(param_2,param_4,local_c), iVar1 == 0) {
      pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
      if (local_c == pcVar2) goto LAB_0048a7fc;
      local_c = local_c + -1;
    }
    pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
    iVar1 = (int)local_c - (int)pcVar2;
  }
  return iVar1;
}

