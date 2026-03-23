
void FUN_007fce00(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 *puStack_20;
  undefined4 uStack_1c;
  uint uStack_18;
  undefined1 local_14 [15];
  allocator<char> local_5;
  
  uStack_18 = 0x7fce0e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_18 = (uint)*pbVar1;
  uStack_1c = param_2;
  puStack_20 = local_14;
  uVar2 = FUN_007fd900();
  select_on_container_copy_construction(&puStack_20,uVar2);
  FUN_007fd950();
  return;
}

