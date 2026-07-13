
undefined4 * __thiscall
FUN_005a72e0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849340;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00611aa0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = PopperGunClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0xeaf36895,0xd9356908,param_1 + 0x20,*(undefined4 *)(param_2 + 0x80));
  FUN_00589800(0xeaf36895,0x1af4cf34,param_1 + 0x21,*(undefined4 *)(param_2 + 0x84));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

