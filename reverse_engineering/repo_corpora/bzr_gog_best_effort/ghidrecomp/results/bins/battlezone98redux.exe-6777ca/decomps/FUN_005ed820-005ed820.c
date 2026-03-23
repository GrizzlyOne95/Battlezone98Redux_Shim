
undefined4 * __thiscall
FUN_005ed820(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084acc0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004f0130(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = TugClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_0047b6c0(0xdd64e901,0xb7295929,param_1 + 0x74,param_1 + 0xac);
  FUN_0047b6c0(0xdd64e901,0xe52080c2,param_1 + 0xa4,param_1 + 0xac);
  FUN_0047b6c0(0xdd64e901,0x8019f006,param_1 + 0xa8,param_1 + 0xac);
  FUN_00589800(0xdd64e901,0x1292ac3d,param_1 + 0x17c,*(undefined4 *)(param_2 + 0x5f0));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

