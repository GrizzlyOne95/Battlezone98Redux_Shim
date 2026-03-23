
void FUN_006cacd0(void)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 local_30 [8];
  allocator<char> *local_28;
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004fbb60();
  puVar3 = local_30;
  uVar1 = std::allocator<char>::allocator<char>(local_28);
  puVar2 = local_24;
  FUN_006cf300(puVar2,uVar1,puVar3);
  FUN_006cf2a0(puVar2,uVar1,puVar3);
  FUN_006aba00(local_30,"remote_endpoint");
  FUN_006cb4c0(local_24);
  FUN_0083e885();
  return;
}

