
void __fastcall FUN_00426bc0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008454c6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_0042a4f0(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_004284d0();
  local_8 = 0xffffffff;
  FUN_004281f0();
  ExceptionList = local_10;
  return;
}

