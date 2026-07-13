
void __fastcall FUN_0076ba30(int param_1)

{
  undefined4 uStack_100;
  undefined1 *puStack_fc;
  undefined1 local_f0 [24];
  undefined1 local_d8 [12];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined1 *local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  int local_ac;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d861;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  puStack_fc = (undefined1 *)0x76ba87;
  local_ac = param_1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x90),"**INVALID**");
  puStack_fc = (undefined1 *)0x76ba99;
  FUN_0076f2b0();
  puStack_fc = (undefined1 *)0x76baa5;
  FUN_00769f40();
  local_8 = 0;
  puStack_fc = (undefined1 *)0x76bac1;
  local_c0 = FUN_004bb540();
  local_8._0_1_ = 1;
  puStack_fc = local_d8;
  uStack_100 = 0x76baed;
  local_bc = local_c0;
  local_b4 = FID_conflict_operator_();
  local_8._0_1_ = 2;
  local_c4 = (undefined1 *)&uStack_100;
  local_b0 = local_b4;
  local_c8 = _String_const_iterator<>(local_b4);
  local_cc = FUN_0076f450(local_f0);
  FUN_004bb3b0();
  local_8._0_1_ = 1;
  FUN_004bb3b0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  puStack_fc = (undefined1 *)0x76bb79;
  FUN_0076f350();
  local_b8 = FUN_004170c0();
  local_b8 = local_b8 + -1;
  local_8 = 0xffffffff;
  FUN_00769ff0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

