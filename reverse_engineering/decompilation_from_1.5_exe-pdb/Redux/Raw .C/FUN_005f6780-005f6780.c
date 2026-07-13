
undefined4 * __thiscall
FUN_005f6780(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084acc0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004f0130(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = TurretTankClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0x3e6439ad,0x6d06fa2,param_1 + 0x17c,*(undefined4 *)(param_2 + 0x5f0));
  FUN_00589800(0x3e6439ad,0x9fa4327,param_1 + 0x17d,*(undefined4 *)(param_2 + 0x5f4));
  FUN_00589800(0x3e6439ad,0x74c3a47c,param_1 + 0x17e,*(undefined4 *)(param_2 + 0x5f8));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

