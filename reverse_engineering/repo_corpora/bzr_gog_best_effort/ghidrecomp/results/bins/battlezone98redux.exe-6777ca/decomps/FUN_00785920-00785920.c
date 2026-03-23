
void FUN_00785920(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_88 [64];
  undefined4 local_48 [4];
  undefined4 local_38;
  undefined4 local_28;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = &DAT_008fe1e0;
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_48[0] = DAT_02cc50e0;
  local_28 = DAT_02cc50e0;
  local_38 = 0x3dcccccd;
  puVar1 = (undefined4 *)FUN_0081fe60(local_88,local_48,DAT_02cc50ec + 0x40);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00820180(DAT_02cecf70,DAT_02cecf70,DAT_02cc50f0,local_48);
  FUN_0083e885();
  return;
}

