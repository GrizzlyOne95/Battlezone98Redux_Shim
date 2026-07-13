
exception * __thiscall
FUN_006b7140(exception *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            undefined4 param_3,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_4,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850c1f;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::exception::exception(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = websocketpp::http::exception::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0xc),param_2);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x24),param_4);
  local_8 = CONCAT31(local_8._1_3_,2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x3c),param_5);
  *(undefined4 *)(param_1 + 0x54) = param_3;
  ExceptionList = local_10;
  return param_1;
}

