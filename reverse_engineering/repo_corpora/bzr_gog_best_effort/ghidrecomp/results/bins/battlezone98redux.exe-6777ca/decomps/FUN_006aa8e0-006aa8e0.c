
void __fastcall FUN_006aa8e0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084fe3e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 2;
  FUN_006aa8c0(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8._0_1_ = 1;
  FUN_006aa8a0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006aa880();
  local_8 = 0xffffffff;
  FUN_007641d0();
  ExceptionList = local_10;
  return;
}

