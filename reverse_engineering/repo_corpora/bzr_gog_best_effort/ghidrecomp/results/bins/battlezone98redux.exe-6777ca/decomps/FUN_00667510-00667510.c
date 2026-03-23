
void __fastcall FUN_00667510(int param_1)

{
  undefined1 local_1c [8];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084e2c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = param_1;
  FUN_008422b0(local_1c,param_1 + 0x28,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0xffffffff;
  FUN_00667570();
  ExceptionList = local_10;
  return;
}

