
undefined * __fastcall FUN_00461b20(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008473ce;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2e40 & 1) == 0) {
    DAT_02cc2e40 = DAT_02cc2e40 | 1;
    local_8 = 0;
    FUN_00422260(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
    FUN_0083e979(FUN_008665c0);
  }
  ExceptionList = local_10;
  return &DAT_02cc2e44;
}

