
void FUN_007fcec0(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_30 [4];
  undefined4 uStack_2c;
  undefined1 *puStack_28;
  undefined4 uStack_24;
  uint uStack_20;
  undefined1 local_1c [23];
  allocator<char> local_5;
  
  uStack_20 = 0x7fcece;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_20 = (uint)*pbVar1;
  uStack_24 = param_2;
  puStack_28 = local_1c;
  uStack_2c = 0x7fcee1;
  uVar2 = FUN_007fd9e0();
  select_on_container_copy_construction(auStack_30,uVar2);
  FUN_007fdba0();
  return;
}

