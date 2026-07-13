
void FUN_007db350(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined4 uStack_14;
  uint uStack_10;
  undefined1 local_c [7];
  allocator<char> local_5;
  
  uStack_10 = 0x7db35e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_10 = (uint)*pbVar1;
  uStack_14 = param_2;
  uVar2 = FUN_007dcd50(local_c);
  select_on_container_copy_construction(&uStack_14,uVar2);
  FUN_007dcda0();
  return;
}

