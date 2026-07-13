
void FUN_0083a167(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 local_28 [2];
  int local_20 [2];
  int local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piVar1 = *(int **)(param_1 + 0x30);
  FUN_0083ad61(param_1,local_20);
  if (local_20[0] == 0xd) {
    iVar2 = *(int *)(*piVar1 + 0xc);
    *(uint *)(iVar2 + local_18 * 4) = *(uint *)(iVar2 + local_18 * 4) & 0xff807fff | 0x4000;
  }
  else {
    local_28[0] = 0;
    FUN_00839805(param_1,local_28,1);
  }
  FUN_0083e885();
  return;
}

