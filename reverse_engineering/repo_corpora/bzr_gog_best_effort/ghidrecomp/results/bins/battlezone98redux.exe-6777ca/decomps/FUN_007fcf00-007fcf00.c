
void FUN_007fcf00(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_40 [12];
  undefined4 uStack_34;
  undefined1 *puStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  undefined1 local_24 [31];
  allocator<char> local_5;
  
  uStack_28 = 0x7fcf0e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_28 = (uint)*pbVar1;
  uStack_2c = param_2;
  puStack_30 = local_24;
  uStack_34 = 0x7fcf21;
  uVar2 = FUN_007fdc30();
  select_on_container_copy_construction(auStack_40,uVar2);
  FUN_007fdc80();
  return;
}

