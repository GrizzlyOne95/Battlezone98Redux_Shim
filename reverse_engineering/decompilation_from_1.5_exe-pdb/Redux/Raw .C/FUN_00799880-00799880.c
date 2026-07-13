
void __fastcall FUN_00799880(int param_1)

{
  undefined4 uVar1;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f5f0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_007cb0c0(local_14);
  (**(code **)(**(int **)(param_1 + 0x16c) + 0x3c))(uVar1);
  FUN_007997a0();
  basic_string<>();
  local_8 = 0;
  uVar1 = FUN_007cb0c0();
  basic_string<>(uVar1);
  local_8._0_1_ = 1;
  FUN_007a4460(local_2c,local_44);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

