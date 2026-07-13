
undefined4 * __thiscall
FUN_005dd920(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
  *param_1 = SupplyDepotClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0x7e56e2e8,0x1f80fefb,param_1 + 0x58,*(undefined4 *)(param_2 + 0x160));
  FUN_00589800(0x7e56e2e8,0xbc6c4e61,param_1 + 0x59,*(undefined4 *)(param_2 + 0x164));
  FUN_00589760(0x7e56e2e8,0x5c81dbd2,param_1 + 0x5a,*(undefined4 *)(param_2 + 0x168));
  FUN_0047b6c0(0x7e56e2e8,0xb1d46bcd,param_1 + 0x5b,param_2 + 0x16c);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

