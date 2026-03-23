
int __thiscall FUN_00417ba0(int *param_1,uint param_2)

{
  _Locimp *p_Var1;
  int local_18;
  int local_c;
  
  if (param_2 < *(uint *)(*param_1 + 0xc)) {
    local_c = *(int *)(*(int *)(*param_1 + 8) + param_2 * 4);
  }
  else {
    local_c = 0;
  }
  local_18 = local_c;
  if ((local_c == 0) && (*(char *)(*param_1 + 0x14) != '\0')) {
    p_Var1 = std::locale::_Getgloballocale();
    if (param_2 < *(uint *)(p_Var1 + 0xc)) {
      local_18 = *(int *)(*(int *)(p_Var1 + 8) + param_2 * 4);
    }
    else {
      local_18 = 0;
    }
  }
  return local_18;
}

