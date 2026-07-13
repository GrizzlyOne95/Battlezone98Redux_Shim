
undefined4 * __thiscall FUN_006be210(undefined4 *param_1,ios_base *param_2)

{
  int iVar1;
  
  *param_1 = param_2;
  iVar1 = std::ios_base::flags(param_2);
  param_1[1] = iVar1;
  return param_1;
}

