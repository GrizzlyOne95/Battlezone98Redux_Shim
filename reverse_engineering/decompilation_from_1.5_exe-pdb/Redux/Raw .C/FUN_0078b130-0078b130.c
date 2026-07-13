
void FUN_0078b130(int param_1)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DAT_00918133 = 1;
  local_14 = uVar1;
  FUN_007c9170(0);
  FUN_0078bb00(uVar1,extraout_var);
  FUN_007c7930(0x17);
  basic_string<>(&DAT_008a1ad8);
  local_8 = 0;
  FUN_00482860(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  FUN_004fddc0(param_1 + 1);
  DAT_00918328 = 0;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

