
void FUN_007daf30(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_58 [24];
  undefined4 uStack_40;
  undefined1 *puStack_3c;
  undefined4 uStack_38;
  uint uStack_34;
  undefined1 local_30 [43];
  allocator<char> local_5;
  
  uStack_34 = 0x7daf3e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_34 = (uint)*pbVar1;
  uStack_38 = param_2;
  puStack_3c = local_30;
  uStack_40 = 0x7daf51;
  uVar2 = FUN_007dc670();
  select_on_container_copy_construction(auStack_58,uVar2);
  FUN_007dc6c0();
  return;
}

