
undefined4 * __thiscall
FUN_006f53e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_4,
            undefined4 param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085527b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = param_2;
  param_1[1] = param_3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 2),param_4);
  local_8 = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  FUN_006f64c0(param_5);
  ExceptionList = local_10;
  return param_1;
}

