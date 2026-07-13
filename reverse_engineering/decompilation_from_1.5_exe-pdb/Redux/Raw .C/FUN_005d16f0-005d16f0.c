
undefined4 * __thiscall
FUN_005d16f0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008494e0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0047ffd0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = ShieldTowerClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0xbca7f8b7,0xe4ca43fc,param_1 + 0x58,*(undefined4 *)(param_2 + 0x160));
  FUN_00589800(0xbca7f8b7,0x7fb47d32,param_1 + 0x5b,*(undefined4 *)(param_2 + 0x16c));
  FUN_00589800(0xbca7f8b7,0xe5ca458f,param_1 + 0x59,*(undefined4 *)(param_2 + 0x164));
  FUN_00589800(0xbca7f8b7,0x80b47ec5,param_1 + 0x5c,*(undefined4 *)(param_2 + 0x170));
  FUN_00589800(0xbca7f8b7,0xe6ca4722,param_1 + 0x5a,*(undefined4 *)(param_2 + 0x168));
  FUN_00589800(0xbca7f8b7,0x7db47a0c,param_1 + 0x5d,*(undefined4 *)(param_2 + 0x174));
  FUN_00589800(0xbca7f8b7,0xd5099ea,param_1 + 0x5e,*(undefined4 *)(param_2 + 0x178));
  FUN_00589800(0xbca7f8b7,0x27970654,param_1 + 0x5f,*(undefined4 *)(param_2 + 0x17c));
  FUN_00589800(0xbca7f8b7,0x1ad95fc4,param_1 + 0x60,*(undefined4 *)(param_2 + 0x180));
  FUN_00589800(0xbca7f8b7,0x5b205972,param_1 + 0x61,*(undefined4 *)(param_2 + 0x184));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

