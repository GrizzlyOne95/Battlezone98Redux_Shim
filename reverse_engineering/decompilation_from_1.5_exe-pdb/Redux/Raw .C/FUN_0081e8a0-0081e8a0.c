
undefined * FUN_0081e8a0(void)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008650fe;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc39dc & 1) == 0) {
    DAT_02cc39dc = DAT_02cc39dc | 1;
    local_8 = 0;
    FUN_0081e220("BZChatLog.txt",0);
    FUN_0083e979(FUN_00868180,uVar1);
  }
  ExceptionList = local_10;
  return &DAT_02cc39e8;
}

