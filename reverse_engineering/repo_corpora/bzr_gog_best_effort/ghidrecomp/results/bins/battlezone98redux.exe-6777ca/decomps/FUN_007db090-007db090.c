
void FUN_007db090(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined1 auStack_124 [108];
  undefined4 uStack_b8;
  undefined1 *puStack_b4;
  undefined4 uStack_b0;
  uint uStack_ac;
  uint uStack_a8;
  undefined1 *local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  allocator<char> local_91;
  undefined1 local_90 [124];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086324b;
  local_10 = ExceptionList;
  uStack_a8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_ac = 0x7db0c6;
  local_14 = uStack_a8;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_91);
  uStack_ac = (uint)*pbVar1;
  uStack_b0 = param_2;
  puStack_b4 = local_90;
  uStack_b8 = 0x7db0dc;
  local_9c = FUN_007dc890();
  local_8 = 0;
  local_a4 = auStack_124;
  local_98 = local_9c;
  local_a0 = FUN_007dc8d0(auStack_124,local_9c);
  FUN_007dc900();
  local_8 = 0xffffffff;
  uStack_ac = 0x7db136;
  FUN_007dba30();
  ExceptionList = local_10;
  uStack_a8 = 0x7db14b;
  FUN_0083e885();
  return;
}

