
undefined4 * __thiscall
FUN_0047dc20(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847970;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e8010(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = BounceBombClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0x5e574933,0xa7666fac,param_1 + 0x34,*(undefined4 *)(param_2 + 0xd0));
  FUN_0047b6c0(0x5e574933,0x7e5a762c,param_1 + 0x35,param_2 + 0xd4);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

