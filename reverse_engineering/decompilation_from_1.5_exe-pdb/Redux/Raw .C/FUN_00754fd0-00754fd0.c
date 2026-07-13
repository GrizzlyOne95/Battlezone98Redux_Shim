
void __fastcall FUN_00754fd0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c399;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cNetFriendsGog::vftable;
  param_1[0xc] = cNetFriendsGog::vftable;
  param_1[0xe] = cNetFriendsGog::vftable;
  param_1[0x10] = cNetFriendsGog::vftable;
  param_1[0x12] = cNetFriendsGog::vftable;
  local_8 = 3;
  FUN_007561c0(uVar1);
  local_8._0_1_ = 2;
  FUN_00756050();
  local_8._0_1_ = 1;
  FUN_00755ee0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00755d70();
  local_8 = 0xffffffff;
  FUN_00753770();
  ExceptionList = local_10;
  return;
}

