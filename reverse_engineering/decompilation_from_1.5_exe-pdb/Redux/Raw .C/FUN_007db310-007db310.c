
void FUN_007db310(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_78 [40];
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  undefined1 local_40 [59];
  allocator<char> local_5;
  
  uStack_44 = 0x7db31e;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_44 = (uint)*pbVar1;
  uStack_48 = param_2;
  puStack_4c = local_40;
  uStack_50 = 0x7db331;
  uVar2 = FUN_007dcc70();
  select_on_container_copy_construction(auStack_78,uVar2);
  FUN_007dccc0();
  return;
}

