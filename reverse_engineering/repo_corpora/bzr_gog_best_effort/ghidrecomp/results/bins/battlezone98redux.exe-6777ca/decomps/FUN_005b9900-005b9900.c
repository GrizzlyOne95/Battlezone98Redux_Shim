
undefined4 * __thiscall
FUN_005b9900(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
  *param_1 = RepairDepotClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0xaa3067d6,0xec53dbd9,param_1 + 0x58,*(undefined4 *)(param_2 + 0x160));
  FUN_00589800(0xaa3067d6,0x361c9203,param_1 + 0x59,*(undefined4 *)(param_2 + 0x164));
  FUN_00589800(0xaa3067d6,&DAT_00ce3138,param_1 + 0x5a,*(undefined4 *)(param_2 + 0x168));
  FUN_0047b6c0(0xaa3067d6,0x7982020b,param_1 + 0x5b,param_2 + 0x16c);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

