
void FUN_007db030(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_70 [36];
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  undefined1 local_3c [55];
  allocator<char> local_5;
  
  uStack_40 = 0x7db03e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_40 = (uint)*pbVar1;
  uStack_44 = param_2;
  puStack_48 = local_3c;
  uStack_4c = 0x7db051;
  uVar2 = FUN_007dc7b0();
  select_on_container_copy_construction(auStack_70,uVar2);
  FUN_007dc800();
  return;
}

