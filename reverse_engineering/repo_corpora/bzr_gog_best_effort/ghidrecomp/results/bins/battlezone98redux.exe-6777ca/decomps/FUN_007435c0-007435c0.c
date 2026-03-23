
undefined4 * __thiscall FUN_007435c0(undefined4 *param_1,undefined4 *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008458bb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = *param_2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 1));
  local_8 = 0;
  *(undefined1 *)(param_1 + 7) = *(undefined1 *)(param_2 + 7);
  param_1[8] = param_2[8];
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 9),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 9));
  *(undefined1 *)(param_1 + 0xf) = *(undefined1 *)(param_2 + 0xf);
  *(undefined1 *)((int)param_1 + 0x3d) = *(undefined1 *)((int)param_2 + 0x3d);
  *(undefined1 *)((int)param_1 + 0x3e) = *(undefined1 *)((int)param_2 + 0x3e);
  param_1[0x10] = param_2[0x10];
  param_1[0x11] = param_2[0x11];
  param_1[0x12] = param_2[0x12];
  *(undefined1 *)(param_1 + 0x13) = *(undefined1 *)(param_2 + 0x13);
  param_1[0x14] = param_2[0x14];
  *(undefined1 *)(param_1 + 0x15) = *(undefined1 *)(param_2 + 0x15);
  ExceptionList = local_10;
  return param_1;
}

