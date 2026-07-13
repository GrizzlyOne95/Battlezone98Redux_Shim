
void __fastcall FUN_005b8e30(int param_1)

{
  char cVar1;
  int iVar2;
  undefined2 *local_114;
  uint local_110;
  undefined2 local_108;
  undefined2 local_106 [127];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_108 = 0x7878;
  local_114 = local_106;
  for (local_110 = 0; local_110 < 4; local_110 = local_110 + 1) {
    if (*(int *)(param_1 + 0xe0 + local_110 * 4) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0xe0 + local_110 * 4) + 0x78) = 0;
      iVar2 = FUN_00572a70();
      if ((iVar2 != 0) && (*(int *)(param_1 + 0xd4) != 0)) {
        cVar1 = FUN_004b9860();
        if (cVar1 != '\0') {
          *local_114 = *(undefined2 *)(*(int *)(param_1 + 0xe0 + local_110 * 4) + 0x7e);
          local_114 = local_114 + 1;
        }
      }
    }
    *(undefined4 *)(param_1 + 0xe0 + local_110 * 4) = 0;
  }
  iVar2 = FUN_00572a70();
  if ((iVar2 != 0) && (*(int *)(param_1 + 0xd4) != 0)) {
    cVar1 = FUN_004b9860();
    if ((cVar1 != '\0') && (local_106 < local_114)) {
      FUN_00575890(&local_108,(int)local_114 - (int)&local_108,1,1);
    }
  }
  FUN_0083e885();
  return;
}

