
void __fastcall FUN_00757d20(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c63e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cNetFriendsSteam::vftable;
  local_8 = 2;
  FUN_00757d00(uVar1);
  local_8._0_1_ = 1;
  FUN_00750aa0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00757ce0();
  local_8 = 0xffffffff;
  FUN_00753770();
  ExceptionList = local_10;
  return;
}

