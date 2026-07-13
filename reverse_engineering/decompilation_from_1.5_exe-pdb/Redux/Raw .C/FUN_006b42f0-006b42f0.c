
void __fastcall FUN_006b42f0(int param_1)

{
  int iVar1;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850840;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006c8f00(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006c8ce0(param_1 + 0x18);
  local_8._0_1_ = 1;
  for (local_14 = 0; local_14 < 0xc1; local_14 = local_14 + 1) {
    iVar1 = get();
    if (iVar1 != 0) {
      FUN_006d8a70(iVar1 + 0x3c);
      FUN_006d8a70(iVar1 + 0x44);
    }
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006c8d50();
  local_8 = 0xffffffff;
  FUN_006c8f30();
  ExceptionList = local_10;
  return;
}

