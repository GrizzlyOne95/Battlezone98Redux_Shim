
undefined1 FUN_007e6b10(void)

{
  undefined4 in_stack_00000084;
  undefined1 auStack_ac [128];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863598;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_11 = 0;
  uStack_28 = 0;
  uStack_2c = in_stack_00000084;
  local_1c = auStack_ac;
  local_20 = FUN_007dd670(&stack0x00000004);
  local_13 = FUN_007e8a60();
  local_8 = 0xffffffff;
  uStack_28 = 0x7e6b87;
  local_12 = local_13;
  FUN_007dba10();
  ExceptionList = local_10;
  return local_13;
}

