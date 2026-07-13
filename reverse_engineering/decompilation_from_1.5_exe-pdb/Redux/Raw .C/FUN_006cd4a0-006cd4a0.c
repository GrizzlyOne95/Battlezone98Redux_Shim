
void __fastcall FUN_006cd4a0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008507de;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 2;
  FUN_006c8f30(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8._0_1_ = 1;
  FUN_006c8f30();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ac0b0();
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

