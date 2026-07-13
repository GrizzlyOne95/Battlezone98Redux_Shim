
undefined4 * __thiscall
FUN_0046d5a0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847560;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005be350(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = AnchorRocketClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0xec437ec4,0x27bac631,param_1 + 0x34,*(undefined4 *)(param_2 + 0xd0));
  FUN_00589800(0xec437ec4,0xc0783809,param_1 + 0x35,*(undefined4 *)(param_2 + 0xd4));
  FUN_00589800(0xec437ec4,0x10d7bd55,param_1 + 0x36,*(undefined4 *)(param_2 + 0xd8));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

