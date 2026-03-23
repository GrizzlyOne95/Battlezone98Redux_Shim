
void FUN_007d4300(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> local_ec [160];
  undefined4 local_4c;
  uint local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862d23;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = 0;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  basic_string<>(uVar1);
  local_8._0_1_ = 1;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
            (local_ec,CONCAT44(param_3,param_2));
  local_4c = GetPolicy(local_44);
  FUN_0045e0f0(local_4c);
  ~basic_string<>();
  basic_string<>(local_2c);
  local_48 = local_48 | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

