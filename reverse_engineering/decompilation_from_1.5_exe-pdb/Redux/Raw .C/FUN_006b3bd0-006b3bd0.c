
void __fastcall FUN_006b3bd0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085076c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 3;
  FUN_006b3c60(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8._0_1_ = 2;
  FUN_006c8e70();
  local_8._0_1_ = 1;
  FUN_006ca250();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca1c0();
  local_8 = 0xffffffff;
  FUN_006ac0b0();
  ExceptionList = local_10;
  return;
}

