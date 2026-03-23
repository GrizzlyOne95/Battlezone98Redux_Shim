
undefined4 * __thiscall FUN_00608d40(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847718;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00461580(param_2,param_3);
  local_8 = 0;
  *param_1 = UserProcess::vftable;
  param_1[7] = 0;
  param_1[8] = 0;
  FUN_0060b650(uVar1);
  ExceptionList = local_10;
  return param_1;
}

