
void FUN_00611610(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_cc [64];
  int local_8c;
  undefined1 local_88 [64];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_006116a0(local_88,0);
  puVar3 = (undefined4 *)(local_8c + 0x28);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_008203f0(local_cc,local_8c + 0x28);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_48;
  puVar3 = (undefined4 *)(local_8c + 0x68);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_0083e885();
  return;
}

