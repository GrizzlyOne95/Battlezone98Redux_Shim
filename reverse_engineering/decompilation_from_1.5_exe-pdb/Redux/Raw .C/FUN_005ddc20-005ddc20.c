
void FUN_005ddc20(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_3bc [472];
  int local_1e4;
  undefined4 local_1e0 [118];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_00918368 = FUN_0068bed0("targetunderlay");
  puVar1 = (undefined4 *)
           FUN_00688370(local_3bc,&DAT_02cecee0,0x3f5f66f3,0x3f800000,0x437a0000,0x3f800000);
  puVar3 = local_1e0;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_1e0;
  puVar3 = (undefined4 *)(local_1e4 + 0x18);
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(local_1e4 + 8) = 0;
  *(undefined4 *)(local_1e4 + 0xc) = 0;
  *(undefined4 *)(local_1e4 + 0x10) = 0;
  *(undefined1 *)(local_1e4 + 0x1f0) = 0;
  *(undefined1 *)(local_1e4 + 0x1f1) = 0;
  FUN_0083e885();
  return;
}

