
undefined4 FUN_007fdb10(void)

{
  undefined1 auStack_58 [12];
  undefined4 uStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863338;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_48 = 0;
  local_20 = auStack_58;
  FUN_007fe060(&stack0x00000004);
  local_1c = FUN_007fede0();
  local_8 = 0;
  uStack_48 = local_14;
  uStack_4c = 0x7fdb6f;
  local_18 = local_1c;
  FUN_007ddb70();
  local_8 = 0xffffffff;
  uStack_48 = 0x7fdb7e;
  FUN_007d7950();
  ExceptionList = local_10;
  return local_14;
}

