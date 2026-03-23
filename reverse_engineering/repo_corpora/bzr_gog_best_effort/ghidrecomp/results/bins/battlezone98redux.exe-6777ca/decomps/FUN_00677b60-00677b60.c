
undefined * FUN_00677b60(void)

{
  uint uVar1;
  undefined4 extraout_var;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084f0ce;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc2c0c & 1) == 0) {
    DAT_02cc2c0c = DAT_02cc2c0c | 1;
    local_8 = 0;
    basic_string<>("DynamicGeometry");
    FUN_0083e979(FUN_00867820,uVar1,extraout_var);
  }
  ExceptionList = local_10;
  return &DAT_02cc2bf4;
}

