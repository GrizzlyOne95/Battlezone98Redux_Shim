
void FUN_007527e0(undefined4 param_1,char param_2)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  uint uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar3 = 0;
  local_14 = uVar1;
  basic_string<>(&DAT_008a1ad8);
  local_8 = 0;
  uVar2 = extraout_var;
  if (param_2 == 'S') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"stratgy.png");
  }
  else if (param_2 == 'D') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"dmatch.png");
  }
  else if (param_2 == 'K') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"king.png");
  }
  else if (param_2 == 'M') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"mpi.png");
  }
  else if (param_2 == 'A') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"api.png");
  }
  basic_string<>(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,uVar2,uVar3 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

