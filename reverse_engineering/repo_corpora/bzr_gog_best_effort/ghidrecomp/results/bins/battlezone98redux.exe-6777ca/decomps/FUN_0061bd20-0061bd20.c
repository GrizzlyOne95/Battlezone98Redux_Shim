
void FUN_0061bd20(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_424 [472];
  uint local_24c;
  uint local_248;
  undefined4 *local_244;
  undefined4 local_240 [142];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24c = (uint)(DAT_008eaad8 == 0xc);
  local_248 = local_24c;
  if (local_24c != 0) {
    puVar1 = &DAT_008eaad0;
    puVar3 = local_240;
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_0061a080();
  }
  iVar2 = FUN_0049f500();
  if (iVar2 != 0) {
    if (DAT_008eaad8 == 4) {
      FUN_0061a080();
    }
    DAT_008ead0c = 0;
    DAT_008eaab0 = 1;
    FUN_00588ba0(*param_1);
    local_244 = (undefined4 *)FUN_00439e60();
    fVar4 = (float10)FUN_00588bc0();
    puVar1 = (undefined4 *)
             FUN_00688370(local_424,local_244[0xe],0x3fc90fda,local_244[0xb],0x447a0000,(float)fVar4
                         );
    puVar3 = local_244;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    DAT_008eaad4 = 0;
    DAT_008eaad8 = 3;
    DAT_008eacb8 = param_1;
    DAT_008eaad0 = FUN_0061bc90;
    FUN_005b0900(0);
    if (local_248 != 0) {
      FUN_0061a000();
      puVar1 = local_240;
      puVar3 = &DAT_008eaad0;
      for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

