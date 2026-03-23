
void FUN_007db170(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined1 auStack_84 [28];
  undefined4 uStack_68;
  undefined1 *puStack_64;
  undefined4 uStack_60;
  uint uStack_5c;
  uint uStack_58;
  undefined1 *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  allocator<char> local_41;
  undefined1 local_40 [44];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863288;
  local_10 = ExceptionList;
  uStack_58 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_5c = 0x7db1a0;
  local_14 = uStack_58;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_41);
  uStack_5c = (uint)*pbVar1;
  uStack_60 = param_2;
  puStack_64 = local_40;
  uStack_68 = 0x7db1b3;
  local_4c = FUN_007dc9a0();
  local_8 = 0;
  local_54 = auStack_84;
  local_48 = local_4c;
  local_50 = FUN_007dc9e0(auStack_84,local_4c);
  FUN_007dca10();
  local_8 = 0xffffffff;
  uStack_5c = 0x7db1f8;
  FUN_007dba70();
  ExceptionList = local_10;
  uStack_58 = 0x7db20d;
  FUN_0083e885();
  return;
}

