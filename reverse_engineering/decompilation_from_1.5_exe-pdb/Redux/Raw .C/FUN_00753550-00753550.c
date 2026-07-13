
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_00753550(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c199;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,param_2);
  local_8 = 0;
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_1 + 0x20,param_2 + 0x20);
  local_8._0_1_ = 1;
  param_1[0x38] = param_2[0x38];
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_1 + 0x3c,param_2 + 0x3c);
  local_8._0_1_ = 2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_1 + 0x54,param_2 + 0x54);
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_004829d0(param_2 + 0x6c);
  ExceptionList = local_10;
  return param_1;
}

