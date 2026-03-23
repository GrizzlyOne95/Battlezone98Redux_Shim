
undefined4 * __thiscall
FUN_005f1eb0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d060;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004af360(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = TurretCraftClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0xa3bfe245,0x6d06fa2,param_1 + 0xca,*(undefined4 *)(param_2 + 0x328));
  FUN_00589800(0xa3bfe245,0xb8add2a,param_1 + 0xcb,*(undefined4 *)(param_2 + 0x32c));
  FUN_00589800(0xa3bfe245,0x473d5031,param_1 + 0xcc,*(undefined4 *)(param_2 + 0x330));
  FUN_00589800(0xa3bfe245,0xdd47602d,param_1 + 0xcd,*(undefined4 *)(param_2 + 0x334));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

