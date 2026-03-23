
undefined4 * __thiscall
FUN_004e2f30(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
  *param_1 = GeizerClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589fe0(0xeabc4a72,0x48130c4f,param_1 + 0x58,*(undefined4 *)(param_2 + 0x160));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530(uVar1);
  ExceptionList = local_10;
  return param_1;
}

