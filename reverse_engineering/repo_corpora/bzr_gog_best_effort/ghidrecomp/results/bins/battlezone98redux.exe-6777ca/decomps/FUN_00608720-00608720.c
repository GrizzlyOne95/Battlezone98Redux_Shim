
void __fastcall FUN_00608720(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847688;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = SitSpinTask::vftable;
  local_8 = 0;
  FUN_00417c60(uVar1);
  param_1[2] = 0xd;
  local_8 = 0xffffffff;
  FUN_005fecc0();
  ExceptionList = local_10;
  return;
}

