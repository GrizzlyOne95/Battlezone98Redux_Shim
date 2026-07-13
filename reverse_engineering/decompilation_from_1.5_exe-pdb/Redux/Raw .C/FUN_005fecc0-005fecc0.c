
void __fastcall FUN_005fecc0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084c4e8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = UnitTask::vftable;
  local_8 = 0;
  FUN_0049f450(0);
  local_8 = 0xffffffff;
  FUN_00461ca0(uVar1);
  ExceptionList = local_10;
  return;
}

