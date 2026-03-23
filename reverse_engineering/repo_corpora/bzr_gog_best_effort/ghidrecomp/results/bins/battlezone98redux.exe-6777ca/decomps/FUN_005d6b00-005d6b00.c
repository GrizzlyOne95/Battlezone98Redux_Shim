
undefined4 * __thiscall
FUN_005d6b00(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ca60;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004812d0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = SniperShellClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0x40400f60,0x935b6321,param_1 + 0x1e,*(undefined4 *)(param_2 + 0x78));
  FUN_00589800(0x40400f60,0x6981c907,param_1 + 0x1f,*(undefined4 *)(param_2 + 0x7c));
  if (0.5 < (float)param_1[0x1f]) {
    param_1[0x1f] = 0x3f000000;
  }
  if (10.0 < (float)param_1[0x1e]) {
    param_1[0x1e] = 0x41200000;
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

