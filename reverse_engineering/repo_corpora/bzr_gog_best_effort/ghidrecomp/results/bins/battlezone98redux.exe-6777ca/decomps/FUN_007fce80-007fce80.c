
void FUN_007fce80(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined4 uStack_20;
  uint uStack_1c;
  undefined1 local_18 [19];
  allocator<char> local_5;
  
  uStack_1c = 0x7fce8e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_1c = (uint)*pbVar1;
  uStack_20 = param_2;
  puStack_24 = local_18;
  uStack_28 = 0x7fcea1;
  uVar2 = FUN_007fdac0();
  select_on_container_copy_construction(&uStack_28,uVar2);
  FUN_007fdb10();
  return;
}

