
undefined4 * __thiscall FUN_004f16b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849538;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e54c0(param_2,param_3,1);
  local_8 = 0;
  *param_1 = HuntTask::vftable;
  param_1[0x53] = param_2;
  param_1[0x59] = 0;
  for (local_18 = 0; local_18 < 5; local_18 = local_18 + 1) {
    param_1[local_18 + 0x54] = 0xbf800000;
  }
  FUN_004f1fd0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

