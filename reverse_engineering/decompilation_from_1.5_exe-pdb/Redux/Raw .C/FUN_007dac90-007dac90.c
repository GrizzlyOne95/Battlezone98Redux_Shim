
void FUN_007dac90(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined1 auStack_6c [16];
  undefined4 uStack_5c;
  undefined1 *puStack_58;
  undefined4 uStack_54;
  uint uStack_50;
  uint uStack_4c;
  undefined1 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  allocator<char> local_35;
  undefined1 local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008631d8;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_50 = 0x7dacc0;
  local_14 = uStack_4c;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_35);
  uStack_50 = (uint)*pbVar1;
  uStack_54 = param_2;
  puStack_58 = local_34;
  uStack_5c = 0x7dacd3;
  local_40 = FUN_007dc3c0();
  local_8 = 0;
  local_48 = auStack_6c;
  local_3c = local_40;
  local_44 = FUN_007dc400(auStack_6c,local_40);
  FUN_007dc430();
  local_8 = 0xffffffff;
  uStack_50 = 0x7dad18;
  FUN_007db9b0();
  ExceptionList = local_10;
  uStack_4c = 0x7dad2d;
  FUN_0083e885();
  return;
}

