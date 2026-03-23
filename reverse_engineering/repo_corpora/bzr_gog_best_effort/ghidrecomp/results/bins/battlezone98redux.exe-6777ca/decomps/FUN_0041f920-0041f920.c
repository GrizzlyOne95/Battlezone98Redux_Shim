
undefined4 * __thiscall FUN_0041f920(undefined4 *param_1,undefined4 param_2,bool param_3)

{
  bool bVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845178;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00422890(param_2);
  local_8 = 0;
  bVar1 = std::basic_istream<char,struct_std::char_traits<char>_>::_Ipfx
                    ((basic_istream<char,struct_std::char_traits<char>_> *)*param_1,param_3);
  *(bool *)(param_1 + 1) = bVar1;
  ExceptionList = local_10;
  return param_1;
}

