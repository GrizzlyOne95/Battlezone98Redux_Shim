
undefined4 * __thiscall
FUN_00660d10(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008494e0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047ffd0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = PortalClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0,0x9af59ffc,param_1 + 0x58,*(undefined4 *)(param_2 + 0x160));
  FUN_0047b6c0(0,0x9142dee5,param_1 + 0x59,param_2 + 0x164);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

