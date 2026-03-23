
undefined4 * __thiscall FUN_0074a810(undefined4 *param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ba66;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = cUser::vftable;
  FUN_0073a740(param_2 + 8);
  FUN_0073a740(param_2 + 0x18);
  *(undefined2 *)(param_1 + 10) = *(undefined2 *)(param_2 + 0x28);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0xb),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x2c));
  local_8 = 0;
  *(undefined1 *)(param_1 + 0x11) = *(undefined1 *)(param_2 + 0x44);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x12),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x48));
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined1 *)(param_1 + 0x18) = *(undefined1 *)(param_2 + 0x60);
  *(undefined1 *)((int)param_1 + 0x61) = *(undefined1 *)(param_2 + 0x61);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x19),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 100));
  *(undefined1 *)(param_1 + 0x1f) = *(undefined1 *)(param_2 + 0x7c);
  param_1[0x20] = *(undefined4 *)(param_2 + 0x80);
  param_1[0x21] = *(undefined4 *)(param_2 + 0x84);
  param_1[0x22] = *(undefined4 *)(param_2 + 0x88);
  *(undefined1 *)(param_1 + 0x23) = *(undefined1 *)(param_2 + 0x8c);
  param_1[0x24] = *(undefined4 *)(param_2 + 0x90);
  *(undefined2 *)(param_1 + 0x25) = *(undefined2 *)(param_2 + 0x94);
  ExceptionList = local_10;
  return param_1;
}

