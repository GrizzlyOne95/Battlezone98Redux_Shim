
void FUN_007c6760(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_3e0 [472];
  undefined1 local_208 [8];
  undefined1 local_200 [4];
  undefined1 local_1fc [4];
  undefined1 local_1f8 [4];
  undefined1 local_1f4 [4];
  float local_1f0;
  int *local_1ec;
  float local_1e8;
  int local_1e4;
  undefined4 local_1e0 [118];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0044d2a0();
  local_1ec = *(int **)(iVar1 + 0xc);
  (**(code **)(*local_1ec + 0x148))(local_1fc,local_1f8,local_200,local_208,local_1f4);
  local_1e8 = (float)DAT_02cecee4 / 480.0;
  local_1f0 = (float)DAT_02cecee0 / 640.0;
  if (local_1f0 < local_1e8) {
    local_1e8 = local_1f0;
  }
  FUN_00689ec0(local_1e8,local_1e8);
  if (DAT_008eaad8 == 0xc) {
    local_1e4 = FUN_00417780(&DAT_02cecee0);
    if (((local_1e4 != 0) && (*(int *)(local_1e4 + 8) < *(int *)(local_1e4 + 0x10))) &&
       (*(int *)(local_1e4 + 0xc) < *(int *)(local_1e4 + 0x14))) {
      puVar2 = (undefined4 *)
               FUN_00688370(local_3e0,local_1e4,0x3fb2b8c2,0x3f800000,0x43960000,0x3f800000);
      puVar3 = local_1e0;
      for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_1e0;
      puVar3 = &DAT_008eaae0;
      for (iVar1 = 0x76; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

