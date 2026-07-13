
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061ab00(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_434 [472];
  undefined1 local_25c [16];
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
  if (DAT_008eaad8 == 4) {
    FUN_0061a080();
  }
  DAT_008ead0c = 0;
  DAT_008eaab0 = 0;
  local_244 = (undefined4 *)FUN_00439e60();
  puVar1 = (undefined4 *)
           FUN_00688370(local_434,local_244[0xe],0x3fb2b8c2,local_244[0xb],local_244[4],DAT_008ead10
                       );
  puVar3 = local_244;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_0081f1e0(local_25c,*param_1 + 0x20);
  _DAT_008eace8 = *puVar1;
  _DAT_008eacec = puVar1[1];
  _DAT_008eacf0 = puVar1[2];
  _DAT_008eacf4 = puVar1[3];
  DAT_008eaad4 = 1;
  DAT_008eaad8 = 0;
  DAT_008eacb8 = param_1;
  DAT_008eaad0 = FUN_0061a510;
  DAT_008eacf8 = _DAT_008eace8;
  DAT_008eacfc = _DAT_008eacec;
  DAT_008ead00 = _DAT_008eacf0;
  DAT_008ead04 = _DAT_008eacf4;
  FUN_005b0900(1);
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
  FUN_0083e885();
  return;
}

