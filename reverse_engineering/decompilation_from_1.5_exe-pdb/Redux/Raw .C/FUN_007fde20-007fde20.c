
undefined4 FUN_007fde20(void)

{
  undefined1 auStack_70 [36];
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
  local_20 = auStack_70;
  FUN_007fe0a0(&stack0x00000004);
  local_1c = FUN_007feed0();
  local_8 = 0;
  uStack_48 = local_14;
  uStack_4c = 0x7fde7f;
  local_18 = local_1c;
  FUN_007ddb70();
  local_8 = 0xffffffff;
  uStack_48 = 0x7fde8e;
  FUN_007d7950();
  ExceptionList = local_10;
  return local_14;
}

