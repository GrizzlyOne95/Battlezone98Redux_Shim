
void FUN_007fcce0(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  undefined1 auStack_48 [16];
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  undefined1 local_28 [35];
  allocator<char> local_5;
  
  uStack_2c = 0x7fccee;
  pbVar1 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uStack_2c = (uint)*pbVar1;
  uStack_30 = param_2;
  puStack_34 = local_28;
  uStack_38 = 0x7fcd01;
  uVar2 = FUN_007fd450();
  select_on_container_copy_construction(auStack_48,uVar2);
  FUN_007fd4a0();
  return;
}

