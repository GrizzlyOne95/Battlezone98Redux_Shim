
undefined4 * __fastcall FUN_0073cc40(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085aa60;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cLobby::vftable;
  vector<>(uVar1);
  local_8 = 0;
  FUN_0073a6b0();
  FUN_0073a6b0();
  basic_string<>();
  local_8._0_1_ = 1;
  basic_string<>();
  local_8._0_1_ = 2;
  basic_string<>();
  local_8._0_1_ = 3;
  basic_string<>();
  local_8._0_1_ = 4;
  basic_string<>();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  basic_string<>();
  local_8._0_1_ = 7;
  FUN_0073bbd0();
  local_8._0_1_ = 8;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,9);
  *(undefined1 *)((int)param_1 + 0xb5) = 0;
  param_1[0x3e] = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x3f),"0");
  *(undefined1 *)(param_1 + 0x12) = 1;
  param_1[0x13] = 0;
  *(undefined1 *)(param_1 + 0x2c) = 1;
  *(undefined1 *)((int)param_1 + 0xb2) = 0;
  *(undefined1 *)((int)param_1 + 0xb6) = 0;
  *(undefined1 *)((int)param_1 + 0xb1) = 0;
  *(undefined1 *)(param_1 + 0x2d) = 0;
  *(undefined1 *)((int)param_1 + 0xb7) = 0;
  ExceptionList = local_10;
  return param_1;
}

