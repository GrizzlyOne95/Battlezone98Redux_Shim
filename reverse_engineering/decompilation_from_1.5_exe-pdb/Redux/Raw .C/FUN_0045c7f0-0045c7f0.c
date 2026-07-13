
undefined * __fastcall FUN_0045c7f0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008471ae;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2e3c & 1) == 0) {
    DAT_02cc2e3c = DAT_02cc2e3c | 1;
    local_8 = 0;
    FUN_0045e380(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
    FUN_0083e979(FUN_008665b0);
  }
  ExceptionList = local_10;
  return &DAT_02cc2e2c;
}

