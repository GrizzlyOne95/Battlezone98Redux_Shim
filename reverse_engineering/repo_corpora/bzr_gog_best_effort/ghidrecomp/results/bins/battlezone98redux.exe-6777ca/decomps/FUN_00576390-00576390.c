
void __fastcall FUN_00576390(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 local_24;
  undefined4 local_22;
  undefined4 local_1e;
  undefined4 local_1a;
  undefined1 local_16;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar4 = 0x12;
  if (*(int *)(param_1 + 0x24) == 0) {
    uVar1 = FUN_005d94c0(*(undefined1 *)(param_1 + 0x68),0x12);
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    if (*(int *)(param_1 + 0x24) != 0) {
      Set(param_1);
    }
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    local_24 = 0x5350;
    puVar2 = (undefined4 *)
             std::allocator<char>::allocator<char>(*(allocator<char> **)(param_1 + 0x24));
    local_22 = *puVar2;
    local_1e = puVar2[1];
    local_1a = puVar2[2];
    local_16 = *(undefined1 *)(param_1 + 0x68);
    iVar3 = FUN_007659f0();
    if (iVar3 != 0) {
      FUN_00759710(param_1 + 0x30,&local_24,uVar4,1);
    }
    uVar4 = FUN_0041f870();
    FUN_007d6a70("NetPlayer::SendSpawnPoint from me to %s\n",uVar4);
  }
  FUN_0083e885();
  return;
}

