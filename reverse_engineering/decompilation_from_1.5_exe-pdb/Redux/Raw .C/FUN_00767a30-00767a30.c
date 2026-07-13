
void __fastcall FUN_00767a30(undefined4 *param_1)

{
  undefined1 local_134 [24];
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d3ee;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cWorkshop::vftable;
  vector<>(local_14);
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  vector<>();
  local_8._0_1_ = 4;
  vector<>();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  basic_string<>();
  local_8._0_1_ = 7;
  param_1[0x1f] = 0;
  param_1[0x23] = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x24),"**INVALID**");
  basic_string<>("*.wav");
  local_8._0_1_ = 8;
  FUN_006cf320(local_44);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.ogg");
  local_8._0_1_ = 9;
  FUN_006cf320(local_11c);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.ini");
  local_8._0_1_ = 10;
  FUN_006cf320(local_8c);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.inf");
  local_8._0_1_ = 0xb;
  FUN_006cf320(local_ec);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.jpg");
  local_8._0_1_ = 0xc;
  FUN_006cf320(local_bc);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.txt");
  local_8._0_1_ = 0xd;
  FUN_006cf320(local_2c);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.stb");
  local_8._0_1_ = 0xe;
  FUN_006cf320(local_74);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.des");
  local_8._0_1_ = 0xf;
  FUN_006cf320(local_a4);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.dds");
  local_8._0_1_ = 0x10;
  FUN_006cf320(local_d4);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.png");
  local_8._0_1_ = 0x11;
  FUN_006cf320(local_104);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*.sta");
  local_8._0_1_ = 0x12;
  FUN_006cf320(local_134);
  local_8._0_1_ = 7;
  ~basic_string<>();
  basic_string<>("*mod.material");
  local_8._0_1_ = 0x13;
  FUN_006cf320(local_5c);
  local_8 = CONCAT31(local_8._1_3_,7);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

