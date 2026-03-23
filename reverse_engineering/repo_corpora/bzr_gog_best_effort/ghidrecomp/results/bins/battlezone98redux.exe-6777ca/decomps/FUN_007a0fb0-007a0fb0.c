
void __fastcall FUN_007a0fb0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00860006;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_MultiPlayer_Lobby::vftable;
  local_8 = 9;
  DAT_00945564 = 0;
  FUN_0073cdf0(uVar1);
  local_8._0_1_ = 8;
  ~basic_string<>();
  local_8._0_1_ = 7;
  ~basic_string<>();
  local_8._0_1_ = 6;
  FUN_0041fe20();
  local_8._0_1_ = 5;
  FUN_0041fe20();
  local_8._0_1_ = 4;
  FUN_0041fe20();
  local_8._0_1_ = 3;
  FUN_0041fe20();
  local_8._0_1_ = 2;
  FUN_0041fe20();
  local_8._0_1_ = 1;
  FUN_0041fe20();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0041fe20();
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

