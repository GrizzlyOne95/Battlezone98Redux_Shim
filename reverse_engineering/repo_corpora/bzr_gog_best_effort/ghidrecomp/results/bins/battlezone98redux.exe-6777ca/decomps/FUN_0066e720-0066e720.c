
void FUN_0066e720(undefined4 param_1,undefined4 param_2,char param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar3 = 0;
  local_14 = uVar1;
  basic_string<>(uVar1,0);
  local_8 = 0;
  iVar2 = FUN_004170c0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            (local_2c,iVar2 + 1);
  FUN_00449810(param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_2c,param_3);
  basic_string<>(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,uVar3 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

