
void __fastcall FUN_004d3880(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847688;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = FollowTask::vftable;
  local_8 = 0;
  FUN_004d3b40(uVar1);
  param_1[2] = 0xd;
  if (param_1[0x47] != 0) {
    FUN_004d32e0(param_1[4]);
  }
  local_8 = 0xffffffff;
  FUN_005fecc0();
  ExceptionList = local_10;
  return;
}

