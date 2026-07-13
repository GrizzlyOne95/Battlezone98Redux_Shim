
void __fastcall FUN_004e5a70(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847688;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = GotoTask::vftable;
  local_8 = 0;
  FUN_004e62f0(uVar1);
  param_1[2] = 0xd;
  if ((*(char *)(param_1 + 0x4f) != '\0') && (param_1[0x4d] != 0)) {
    FUN_00460600(param_1[0x4d]);
  }
  local_8 = 0xffffffff;
  FUN_005fecc0();
  ExceptionList = local_10;
  return;
}

