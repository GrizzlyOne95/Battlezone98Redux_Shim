
void __thiscall FUN_005d1ee0(int param_1,float param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int local_10;
  
  for (local_10 = 0; local_10 < *(int *)(param_1 + 0x4b0); local_10 = local_10 + 1) {
    iVar1 = param_1 + 0x30 + local_10 * 0x24;
    *(float *)(iVar1 + 0x20) = param_2 * *(float *)(iVar1 + 0x1c) + *(float *)(iVar1 + 0x20);
    if (*(float *)(iVar1 + 0x20) < (float)*(int *)(param_1 + 0x2c)) {
      *(float *)(iVar1 + 0xc) = *(float *)(iVar1 + 0x14) * param_2 + *(float *)(iVar1 + 0xc);
      *(float *)(iVar1 + 0x10) = *(float *)(iVar1 + 0x18) * param_2 + *(float *)(iVar1 + 0x10);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x4b0) + -1;
      *(int *)(param_1 + 0x4b0) = iVar1;
      puVar3 = (undefined4 *)(param_1 + 0x30 + iVar1 * 0x24);
      puVar4 = (undefined4 *)(param_1 + 0x30 + local_10 * 0x24);
      for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_10 = local_10 + -1;
    }
  }
  return;
}

