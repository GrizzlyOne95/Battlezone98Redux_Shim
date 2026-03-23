
void FUN_0048b7d0(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar3 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  iVar1 = FUN_004170c0();
  iVar2 = FUN_00416290(param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            (local_2c,iVar1 + iVar2);
  FUN_00449810(param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  basic_string<>(local_2c);
  uVar3 = uVar3 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885(uVar3);
  return;
}

