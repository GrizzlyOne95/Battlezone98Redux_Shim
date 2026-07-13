
uint __thiscall
FUN_0045e490(_String_val<struct_std::_Simple_types<char>_> *param_1,undefined4 param_2,uint param_3,
            uint param_4)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint local_14;
  char *local_c;
  
  if (param_4 == 0) {
    if (*(uint *)(param_1 + 0x10) <= param_3) {
      param_3 = *(uint *)(param_1 + 0x10);
    }
  }
  else {
    if (param_4 <= *(uint *)(param_1 + 0x10)) {
      if (param_3 < *(int *)(param_1 + 0x10) - param_4) {
        local_14 = param_3;
      }
      else {
        local_14 = *(int *)(param_1 + 0x10) - param_4;
      }
      local_c = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
      local_c = local_c + local_14;
      while( true ) {
        cVar1 = eq(local_c,param_2);
        if ((cVar1 != '\0') && (iVar2 = FUN_00417a10(local_c,param_2,param_4), iVar2 == 0)) {
          pcVar3 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
          return (int)local_c - (int)pcVar3;
        }
        pcVar3 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
        if (local_c == pcVar3) break;
        local_c = local_c + -1;
      }
    }
    param_3 = 0xffffffff;
  }
  return param_3;
}

