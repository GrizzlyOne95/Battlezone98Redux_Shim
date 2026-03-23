
void FUN_0043bf80(int param_1)

{
  int iVar1;
  int *piVar2;
  int *local_18;
  undefined4 *local_14;
  
  if (*(int *)(param_1 + 100) != -1) {
    DAT_0260c254 = DAT_0260c254 + 1;
    iVar1 = *(int *)(param_1 + 100);
    piVar2 = &DAT_0260c2e8 + iVar1 * 4;
    if (*piVar2 == -1) {
      local_14 = (undefined4 *)0x0;
    }
    else {
      local_14 = &DAT_0260c2e8 + *piVar2 * 4;
    }
    if ((&DAT_0260c2ec)[iVar1 * 4] == -1) {
      local_18 = (int *)0x0;
    }
    else {
      local_18 = &DAT_0260c2e8 + (&DAT_0260c2ec)[iVar1 * 4] * 4;
    }
    if (local_14 != (undefined4 *)0x0) {
      local_14[1] = (&DAT_0260c2ec)[iVar1 * 4];
    }
    if (local_18 != (int *)0x0) {
      *local_18 = *piVar2;
    }
    *piVar2 = -1;
    (&DAT_0260c2ec)[iVar1 * 4] = DAT_0260c2e4;
    (&DAT_0260c2f0)[iVar1 * 4] = 0;
    (&DAT_0260c2f4)[iVar1 * 4] = 0;
    DAT_0260c2e4 = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 100) = 0xffffffff;
  }
  return;
}

