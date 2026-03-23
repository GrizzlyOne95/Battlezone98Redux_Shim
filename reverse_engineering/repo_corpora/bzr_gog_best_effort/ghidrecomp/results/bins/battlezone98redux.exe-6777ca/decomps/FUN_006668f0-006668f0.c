
void __thiscall FUN_006668f0(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00666660(local_14,param_1);
  basic_string<>(param_2);
  local_8 = 0;
  FUN_0042a3e0(local_2c,param_1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

