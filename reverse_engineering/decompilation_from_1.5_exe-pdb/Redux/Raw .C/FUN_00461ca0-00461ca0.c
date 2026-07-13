
void __fastcall FUN_00461ca0(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847428;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = AiTask::vftable;
  local_8 = 0;
  local_18 = param_1;
  local_14 = param_1;
  FUN_0045e290(&local_18);
  local_8 = 0xffffffff;
  FUN_005d7350(uVar1);
  ExceptionList = local_10;
  return;
}

