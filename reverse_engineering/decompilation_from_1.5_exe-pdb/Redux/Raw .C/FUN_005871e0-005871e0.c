
uint __thiscall
FUN_005871e0(_String_val<struct_std::_Simple_types<char>_> *param_1,undefined4 param_2,uint param_3,
            uint param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *local_14;
  int local_8;
  
  if ((param_4 != 0) || (*(uint *)(param_1 + 0x10) < param_3)) {
    if ((param_3 < *(uint *)(param_1 + 0x10)) && (param_4 <= *(int *)(param_1 + 0x10) - param_3)) {
      local_8 = (*(int *)(param_1 + 0x10) - param_3) - (param_4 - 1);
      local_14 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
      local_14 = local_14 + param_3;
      while (iVar1 = FUN_00482540(local_14,local_8,param_2), iVar1 != 0) {
        iVar2 = FUN_00417a10(iVar1,param_2,param_4);
        if (iVar2 == 0) {
          pcVar3 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
          return iVar1 - (int)pcVar3;
        }
        local_8 = local_8 - ((iVar1 - (int)local_14) + 1);
        local_14 = (char *)(iVar1 + 1);
      }
    }
    param_3 = 0xffffffff;
  }
  return param_3;
}

