
void __fastcall FUN_00773b60(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085e206;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_006aa880(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_006aa8a0();
  local_8 = 0xffffffff;
  FUN_00767e30();
  ExceptionList = local_10;
  return;
}

