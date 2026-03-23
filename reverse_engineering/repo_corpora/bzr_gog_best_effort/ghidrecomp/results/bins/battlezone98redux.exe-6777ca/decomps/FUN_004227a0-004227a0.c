
uint __thiscall
FUN_004227a0(_String_val<struct_std::_Simple_types<char>_> *param_1,uint param_2,uint param_3,
            undefined4 param_4,uint param_5)

{
  char *pcVar1;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_c;
  
  if (*(uint *)(param_1 + 0x10) < param_2) {
    FUN_00417440();
  }
  if (*(int *)(param_1 + 0x10) - param_2 < param_3) {
    param_3 = *(int *)(param_1 + 0x10) - param_2;
  }
  if (param_3 < param_5) {
    local_c = param_3;
  }
  else {
    local_c = param_5;
  }
  pcVar1 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
  local_1c = FUN_00417a10(pcVar1 + param_2,param_4,local_c);
  if (local_1c == 0) {
    if (param_3 < param_5) {
      local_18 = 0xffffffff;
    }
    else {
      local_14 = (uint)(param_3 != param_5);
      local_18 = local_14;
    }
    local_1c = local_18;
  }
  return local_1c;
}

