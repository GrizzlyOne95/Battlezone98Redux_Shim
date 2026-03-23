
void FUN_005d6240(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_3bc [472];
  int local_1e4;
  undefined4 local_1e0 [118];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0068bed0("sight");
  *(undefined4 *)(local_1e4 + 8) = uVar1;
  uVar1 = FUN_0068bed0("particle.0");
  *(undefined4 *)(local_1e4 + 0xc) = uVar1;
  puVar2 = (undefined4 *)
           FUN_00688370(local_3bc,&DAT_02cecee0,0x3f901829,0x3f800000,0x43fa0000,0x41200000);
  puVar4 = local_1e0;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_1e0;
  puVar4 = (undefined4 *)(local_1e4 + 0x10);
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined1 *)(local_1e4 + 0x1e8) = 0;
  *(undefined1 *)(local_1e4 + 0x1e9) = 0;
  FUN_0083e885();
  return;
}

