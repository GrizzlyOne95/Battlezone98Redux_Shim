
int __thiscall FUN_0072b3b0(int param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851c71;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0073a740(param_2);
  FUN_0073a740(param_2 + 0x10);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x20),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x20));
  local_8 = 0;
  *(undefined1 *)(param_1 + 0x38) = *(undefined1 *)(param_2 + 0x38);
  *(undefined1 *)(param_1 + 0x39) = *(undefined1 *)(param_2 + 0x39);
  FUN_006ffa70(param_2 + 0x3c);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x44),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x44));
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0072b4e0(param_2 + 0x5c);
  *(undefined1 *)(param_1 + 100) = *(undefined1 *)(param_2 + 100);
  ExceptionList = local_10;
  return param_1;
}

