
void __thiscall FUN_00426a60(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845450;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14,param_1);
  local_8 = 0;
  basic_string<>(param_2);
  local_8._0_1_ = 1;
  FUN_0042a3e0(local_2c,param_1);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

