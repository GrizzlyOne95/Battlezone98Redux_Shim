
undefined4
FUN_007104c0(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008554c1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
         forward<>(0x18,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (this != (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(this,param_2);
  }
  ExceptionList = local_10;
  return 4;
}

