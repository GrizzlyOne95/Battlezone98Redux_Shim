
undefined * FUN_0056e940(void)

{
  undefined1 local_24 [12];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084b526;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc30e0 & 1) == 0) {
    DAT_02cc30e0 = DAT_02cc30e0 | 1;
    local_8 = 0;
    FUN_0045e380(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_0083e979(FUN_00866f10);
  }
  local_8 = 0xffffffff;
  local_18 = FUN_0045dd40(local_24,&DAT_00915540,0,0);
  local_8 = 1;
  local_14 = local_18;
  FUN_0056cc30(local_18);
  local_8 = 0xffffffff;
  FUN_0045c7d0();
  ExceptionList = local_10;
  return &DAT_02cc30e4;
}

