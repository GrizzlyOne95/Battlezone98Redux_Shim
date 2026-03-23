
undefined4 * __thiscall
FUN_0056aad0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847560;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005be350(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = MissileClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0x77aa7cd5,0x4ad4b447,param_1 + 0x34,*(undefined4 *)(param_2 + 0xd0));
  FUN_00589800(0x77aa7cd5,0x21601063,param_1 + 0x35,*(undefined4 *)(param_2 + 0xd4));
  param_1[0x35] = (float)param_1[0x35] / (float)param_1[0x15];
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

