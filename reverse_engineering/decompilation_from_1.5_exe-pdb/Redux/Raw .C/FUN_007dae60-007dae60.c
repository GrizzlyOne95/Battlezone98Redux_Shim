
void FUN_007dae60(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined1 auStack_12c [112];
  undefined4 uStack_bc;
  undefined1 *puStack_b8;
  undefined4 uStack_b4;
  uint uStack_b0;
  uint uStack_ac;
  undefined1 *local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  allocator<char> local_95;
  undefined1 local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086320b;
  local_10 = ExceptionList;
  uStack_ac = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_b0 = 0x7dae96;
  local_14 = uStack_ac;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_95);
  uStack_b0 = (uint)*pbVar1;
  uStack_b4 = param_2;
  puStack_b8 = local_94;
  uStack_bc = 0x7daeac;
  local_a0 = FUN_007dc560();
  local_8 = 0;
  local_a8 = auStack_12c;
  local_9c = local_a0;
  local_a4 = FUN_007dc5a0(auStack_12c,local_a0);
  FUN_007dc5d0();
  local_8 = 0xffffffff;
  uStack_b0 = 0x7daf09;
  FUN_007db9f0();
  ExceptionList = local_10;
  uStack_ac = 0x7daf1e;
  FUN_0083e885();
  return;
}

