
void __fastcall FUN_006b3750(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  allocator<char> local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_006b34f0();
  if (cVar1 == '\0') {
    puVar3 = (undefined4 *)std::allocator<char>::allocator<char>(local_18);
    *puVar3 = *(undefined4 *)(param_1 + 8);
    puVar3[1] = *(undefined4 *)(param_1 + 0xc);
    puVar3[2] = *(undefined4 *)(param_1 + 0x10);
    puVar3[3] = *(undefined4 *)(param_1 + 0x14);
    uVar2 = FUN_006b2f30(local_18,*(undefined4 *)(param_1 + 0x18));
    FUN_006b31d0(uVar2);
  }
  else {
    uVar2 = FUN_006affe0(*(undefined4 *)(param_1 + 4));
    uVar2 = FUN_006b2e00(uVar2);
    FUN_006b3190(uVar2);
  }
  FUN_0083e885();
  return;
}

