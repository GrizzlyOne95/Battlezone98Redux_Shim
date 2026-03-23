
void __fastcall FUN_0074dd70(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085be74;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = CGalaxyLobby::vftable;
  param_1[0x32] = CGalaxyLobby::vftable;
  param_1[0x34] = CGalaxyLobby::vftable;
  param_1[0x36] = CGalaxyLobby::vftable;
  param_1[0x38] = CGalaxyLobby::vftable;
  param_1[0x3a] = CGalaxyLobby::vftable;
  param_1[0x3c] = CGalaxyLobby::vftable;
  param_1[0x3e] = CGalaxyLobby::vftable;
  param_1[0x40] = CGalaxyLobby::vftable;
  param_1[0x42] = CGalaxyLobby::vftable;
  param_1[0x44] = CGalaxyLobby::vftable;
  param_1[0x46] = CGalaxyLobby::vftable;
  local_8 = 10;
  FUN_00750250(uVar1);
  local_8._0_1_ = 9;
  FUN_007500e0();
  local_8._0_1_ = 8;
  FUN_0074ff70();
  local_8._0_1_ = 7;
  FUN_0074fe00();
  local_8._0_1_ = 6;
  FUN_0074fc90();
  local_8._0_1_ = 5;
  FUN_0074fb20();
  local_8._0_1_ = 4;
  FUN_0074f9b0();
  local_8._0_1_ = 3;
  FUN_0074f840();
  local_8._0_1_ = 2;
  FUN_0074f6d0();
  local_8._0_1_ = 1;
  FUN_0074f560();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0074f3f0();
  local_8 = 0xffffffff;
  FUN_0073d510();
  ExceptionList = local_10;
  return;
}

