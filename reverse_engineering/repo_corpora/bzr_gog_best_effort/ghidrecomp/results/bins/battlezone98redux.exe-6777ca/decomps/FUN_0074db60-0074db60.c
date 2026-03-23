
undefined4 * __thiscall FUN_0074db60(undefined4 *param_1,undefined1 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085be74;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0073d690(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_0074f330(0);
  local_8._0_1_ = 1;
  FUN_0074f4a0(0);
  local_8._0_1_ = 2;
  FUN_0074f610(0);
  local_8._0_1_ = 3;
  FUN_0074f780(0);
  local_8._0_1_ = 4;
  FUN_0074f8f0(0);
  local_8._0_1_ = 5;
  FUN_0074fa60(0);
  local_8._0_1_ = 6;
  FUN_0074fbd0(0);
  local_8._0_1_ = 7;
  FUN_0074fd40(0);
  local_8._0_1_ = 8;
  FUN_0074feb0(0);
  local_8._0_1_ = 9;
  FUN_00750020(0);
  local_8 = CONCAT31(local_8._1_3_,10);
  FUN_00750190(0);
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
  *(undefined1 *)(param_1 + 0x48) = 0;
  *(undefined1 *)((int)param_1 + 0x121) = param_2;
  ExceptionList = local_10;
  return param_1;
}

