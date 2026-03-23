
undefined4 FUN_007df400(void)

{
  undefined1 auStack_40 [28];
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863658;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_24 = 0x7df437;
  FUN_00423890();
  local_18 = auStack_40;
  local_1c = FUN_007dd560(&stack0x00000004);
  FUN_007e2850();
  local_8 = 0xffffffff;
  uStack_24 = 0x7df462;
  FUN_007db9d0();
  ExceptionList = local_10;
  return local_14;
}

