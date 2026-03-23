
basic_streambuf<char,struct_std::char_traits<char>_> * __thiscall
FUN_004230e0(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008452e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::basic_streambuf<char,struct_std::char_traits<char>_>::
  basic_streambuf<char,struct_std::char_traits<char>_>(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = std::basic_filebuf<char,struct_std::char_traits<char>_>::vftable;
  FUN_00423280(param_2,0);
  ExceptionList = local_10;
  return param_1;
}

