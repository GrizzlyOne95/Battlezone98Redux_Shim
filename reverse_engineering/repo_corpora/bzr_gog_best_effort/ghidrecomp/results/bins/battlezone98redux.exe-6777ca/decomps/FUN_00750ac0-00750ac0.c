
void __fastcall FUN_00750ac0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c016;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = CSteamLobby::vftable;
  local_8 = 9;
  FUN_007523c0(uVar1);
  local_8._0_1_ = 8;
  FUN_00752230();
  local_8._0_1_ = 7;
  FUN_00750aa0();
  local_8._0_1_ = 6;
  FUN_006aa880();
  local_8._0_1_ = 5;
  FUN_006aa880();
  local_8._0_1_ = 4;
  FUN_006aa8a0();
  local_8._0_1_ = 3;
  FUN_006aa880();
  local_8._0_1_ = 2;
  FUN_00750a80();
  local_8._0_1_ = 1;
  FUN_006aa880();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006aa8a0();
  local_8 = 0xffffffff;
  FUN_0073d510();
  ExceptionList = local_10;
  return;
}

