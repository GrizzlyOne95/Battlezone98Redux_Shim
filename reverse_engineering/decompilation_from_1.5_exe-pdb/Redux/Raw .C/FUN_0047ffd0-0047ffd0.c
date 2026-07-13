
undefined4 * __thiscall
FUN_0047ffd0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008479d0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e0450(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = BuildingClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_0047b6c0(0x91e9360f,0xf1aad7dc,param_1 + 0x54,param_2 + 0x150);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

