
void FUN_006b6650(undefined4 param_1,int param_2,uint param_3)

{
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  uint local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850ba0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar3 = 0;
  local_14 = uVar1;
  basic_string<>(uVar1,0);
  local_8 = 0;
  basic_string<>("0123456789ABCDEF");
  local_8._0_1_ = 1;
  for (local_48 = 0; local_48 < param_3; local_48 = local_48 + 1) {
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](local_44,(int)(*(byte *)(param_2 + local_48) & 0xf0) >> 4);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
              (local_2c,*pcVar2);
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](local_44,*(byte *)(param_2 + local_48) & 0xf);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
              (local_2c,*pcVar2);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c," ");
  }
  basic_string<>(local_2c);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>(uVar1,uVar3 | 1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

