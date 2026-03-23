
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
FUN_00843c60(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            undefined4 param_2)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00865e19;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  local_4 = 0;
  switch(param_2) {
  case 0:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_1,"ok");
    ExceptionList = local_c;
    return param_1;
  case 1:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_1,"partial");
    ExceptionList = local_c;
    return param_1;
  case 2:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_1,"error");
    ExceptionList = local_c;
    return param_1;
  case 3:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (param_1,"noconv");
    ExceptionList = local_c;
    return param_1;
  default:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              (param_1,"unknown error",0xd);
    ExceptionList = local_c;
    return param_1;
  }
}

