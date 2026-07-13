
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fa9a0(int param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *local_10;
  
  for (local_10 = (int *)(param_1 + 0x28);
      local_10 < (int *)(param_1 + 0x28 + *(int *)(param_1 + 0x68) * 4); local_10 = local_10 + 1) {
    iVar1 = *local_10;
    *(float *)(iVar1 + 0x28) = *(float *)(iVar1 + 0x28) - param_2;
    if (*(float *)(iVar1 + 0x28) <= 0.0) {
      if (*(int *)(iVar1 + 0x20) == 0) {
        if (*(int *)(iVar1 + 0x1038) == 0) {
          uVar2 = FUN_00439e60();
          FUN_004fb360(iVar1,uVar2);
        }
        else {
          uVar2 = FUN_00439e60();
          FUN_004fb520(iVar1,uVar2);
        }
        FUN_004fb0d0(iVar1);
        if (DAT_009b7cc4 != '\0') {
          FUN_00437720(&DAT_009b7cc4,*(undefined4 *)(iVar1 + 0x1038),0);
        }
        _DAT_009454a0 = 0;
      }
      if (*(int *)(iVar1 + 0x20) < *(int *)(iVar1 + 0x1c)) {
        *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + 1;
        *(float *)(iVar1 + 0x28) = *(float *)(iVar1 + 0x28) + *(float *)(iVar1 + 0x24);
      }
      else {
        _DAT_009454a0 = 0;
        FUN_004fabb0(iVar1);
      }
    }
  }
  return;
}

