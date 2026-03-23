
undefined4 * __thiscall FUN_0074a970(undefined4 *param_1,int param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bb02;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cLobby::vftable;
  FUN_0074aba0(param_2 + 8,uVar1);
  local_8 = 0;
  FUN_0073a740(param_2 + 0x10);
  FUN_0073a740(param_2 + 0x20);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0xc),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x30));
  local_8._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x12) = *(undefined1 *)(param_2 + 0x48);
  param_1[0x13] = *(undefined4 *)(param_2 + 0x4c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x14),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x50));
  local_8._0_1_ = 2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x1a),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x68));
  local_8._0_1_ = 3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x20),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x80));
  local_8._0_1_ = 4;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x26),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x98));
  local_8._0_1_ = 5;
  *(undefined1 *)(param_1 + 0x2c) = *(undefined1 *)(param_2 + 0xb0);
  *(undefined1 *)((int)param_1 + 0xb1) = *(undefined1 *)(param_2 + 0xb1);
  *(undefined1 *)((int)param_1 + 0xb2) = *(undefined1 *)(param_2 + 0xb2);
  *(undefined1 *)((int)param_1 + 0xb3) = *(undefined1 *)(param_2 + 0xb3);
  *(undefined1 *)(param_1 + 0x2d) = *(undefined1 *)(param_2 + 0xb4);
  *(undefined1 *)((int)param_1 + 0xb5) = *(undefined1 *)(param_2 + 0xb5);
  *(undefined1 *)((int)param_1 + 0xb6) = *(undefined1 *)(param_2 + 0xb6);
  *(undefined1 *)((int)param_1 + 0xb7) = *(undefined1 *)(param_2 + 0xb7);
  FUN_0074ac90(param_2 + 0xb8);
  local_8._0_1_ = 6;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x30),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0xc0));
  local_8._0_1_ = 7;
  FUN_007435c0(param_2 + 0xd8);
  local_8 = CONCAT31(local_8._1_3_,8);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x4c),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x130));
  *(undefined1 *)(param_1 + 0x52) = *(undefined1 *)(param_2 + 0x148);
  ExceptionList = local_10;
  return param_1;
}

