
undefined * FUN_0081e820(void)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008650ce;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc39e0 & 1) == 0) {
    DAT_02cc39e0 = DAT_02cc39e0 | 1;
    local_8 = 0;
    FUN_0081e220("BZLogger.txt",1);
    FUN_0083e979(FUN_00868170,uVar1);
  }
  ExceptionList = local_10;
  return &DAT_02cc3aa8;
}

