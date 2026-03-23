
void FUN_007fad40(uint param_1)

{
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar1;
  code *pcVar2;
  code *pcVar3;
  char *pcVar4;
  undefined1 auStack_e4 [160];
  runtime_error local_44 [12];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_34;
  undefined1 *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008640fb;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xf4) {
    local_30 = (undefined1 *)0x0;
  }
  else {
    local_30 = auStack_e4;
  }
  pcVar4 = " encountered while trying to encode UTF-16 sequence";
  pcVar3 = FUN_00574a10;
  pcVar2 = FUN_007fad20;
  pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_30,"Invalid UTF-32 code point U+");
  pbVar1 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pcVar2);
  pbVar1 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pcVar3);
  pbVar1 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,param_1);
  FUN_004bc590(pbVar1,pcVar4);
  local_38 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             GetPolicy(local_2c);
  local_8._0_1_ = 1;
  local_34 = local_38;
  std::runtime_error::runtime_error(local_44,local_38);
  local_8._0_1_ = 3;
  ~basic_string<>();
  FUN_006d94f0(local_44);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ab660();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

