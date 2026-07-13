
undefined4 FUN_006b5f70(undefined4 param_1)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> local_b8 [160];
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fcab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
            (local_b8,*(ushort *)(local_18 + 0x48));
  GetPolicy(param_1);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10(uVar1);
  ExceptionList = local_10;
  return param_1;
}

