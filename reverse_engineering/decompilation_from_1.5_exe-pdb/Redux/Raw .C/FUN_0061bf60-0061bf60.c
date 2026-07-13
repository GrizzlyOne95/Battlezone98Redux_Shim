
void FUN_0061bf60(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_430 [472];
  uint local_258;
  uint local_254;
  undefined4 *local_250;
  undefined4 local_24c [142];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_258 = (uint)(DAT_008eaad8 == 0xc);
  local_254 = local_258;
  if (local_258 != 0) {
    puVar1 = &DAT_008eaad0;
    puVar3 = local_24c;
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_0061a080();
  }
  if (DAT_008eaad8 == 4) {
    FUN_0061a080();
  }
  DAT_008ead0c = 0;
  DAT_008eaab0 = 1;
  local_250 = (undefined4 *)FUN_00439e60();
  fVar4 = (float10)FUN_004c8240();
  puVar1 = (undefined4 *)
           FUN_00688370(local_430,local_250[0xe],0x3fc90fda,local_250[0xb],0x447a0000,(float)fVar4);
  puVar3 = local_250;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_14 = (float)*(double *)(*param_1 + 0x48);
  local_10 = (float)*(double *)(*param_1 + 0x50);
  local_c = (float)*(double *)(*param_1 + 0x58);
  FUN_004c8290(&local_14);
  DAT_008eaad4 = 0;
  DAT_008eaad8 = 10;
  DAT_008eacb8 = param_1;
  DAT_008eaad0 = FUN_0061bed0;
  FUN_005b0900(0);
  FUN_004c82d0();
  if (local_254 != 0) {
    FUN_0061a000();
    puVar1 = local_24c;
    puVar3 = &DAT_008eaad0;
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  FUN_0083e885();
  return;
}

