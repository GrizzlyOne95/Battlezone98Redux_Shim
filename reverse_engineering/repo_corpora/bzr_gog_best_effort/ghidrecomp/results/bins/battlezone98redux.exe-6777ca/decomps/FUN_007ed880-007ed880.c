
void __fastcall FUN_007ed880(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863feb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007ed9a0(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = 0xffffffff;
  FUN_007d7170();
  ExceptionList = local_10;
  return;
}

