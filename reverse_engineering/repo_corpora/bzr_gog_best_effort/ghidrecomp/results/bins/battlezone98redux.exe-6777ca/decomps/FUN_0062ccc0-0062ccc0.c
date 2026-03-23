
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_0062ccc0(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_20 [12];
  undefined1 local_14 [12];
  int *local_8;
  
  piVar1 = DAT_02b3c724;
  if (DAT_02b3c724 == (int *)0x0) {
    local_8 = calloc(1,0xd8);
  }
  else {
    local_8 = DAT_02b3c724;
    DAT_02b3c724 = (int *)DAT_02b3c724[0x1f];
    memset(piVar1,0,0xd8);
  }
  *local_8 = DAT_02b3c654;
  DAT_02b3c654 = DAT_02b3c654 + 1;
  if (local_8 != (int *)0x0) {
    *(undefined2 *)(local_8 + 4) = 0;
    local_8[6] = -1;
    local_8[5] = 0;
    local_8[0x18] = -1;
    local_8[0x1e] = 0;
    local_8[0x20] = 0;
    local_8[0x1f] = 0;
    local_8[0x19] = 0;
    local_8[0x1a] = 0;
    local_8[0x1b] = 0;
    local_8[0x1c] = 0;
    local_8[0x1d] = 0;
    local_8[0x21] = 0;
    local_8[0x22] = 0;
    local_8[0x25] = 0;
    local_8[0x24] = 0;
    local_8[0x26] = 0;
    local_8[0x27] = 0;
    piVar1 = (int *)FUN_00440000(local_14,0,0,0);
    local_8[0x28] = *piVar1;
    local_8[0x29] = piVar1[1];
    local_8[0x2a] = piVar1[2];
    local_8[0x2b] = 0;
    piVar1 = (int *)FUN_00440000(local_20,0,0,0);
    local_8[0x2f] = *piVar1;
    local_8[0x30] = piVar1[1];
    local_8[0x31] = piVar1[2];
    local_8[0x2c] = local_8[0x2f];
    local_8[0x2d] = local_8[0x30];
    local_8[0x2e] = local_8[0x31];
    piVar1 = &DAT_008fe1e0;
    piVar3 = local_8 + 8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar3 = *piVar1;
      piVar1 = piVar1 + 1;
      piVar3 = piVar3 + 1;
    }
    if (param_1 == 0) {
      _DAT_02a1f56c = local_8;
      _DAT_02b3c728 = local_8;
      *(undefined2 *)((int)local_8 + 0x12) = 1;
    }
    else {
      if (*(int *)(param_1 + 0x80) != 0) {
        local_8[0x1f] = *(int *)(param_1 + 0x80);
      }
      local_8[0x1e] = param_1;
      *(int **)(param_1 + 0x80) = local_8;
      *(undefined2 *)(local_8 + 4) = *(undefined2 *)(param_1 + 0x10);
      *(undefined2 *)((int)local_8 + 0x12) = *(undefined2 *)(param_1 + 0x12);
    }
  }
  return local_8;
}

