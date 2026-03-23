
void __fastcall FUN_004d9970(int param_1)

{
  int iVar1;
  int iVar2;
  int local_30;
  int local_2c;
  uint local_28;
  int local_24;
  int local_20;
  int local_1c [6];
  
  local_1c[5] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = 0;
  for (local_20 = 0; local_20 < 5; local_20 = local_20 + 1) {
    if ((((1 << ((byte)local_20 & 0x1f) & local_28) == 0) &&
        (iVar1 = *(int *)(param_1 + 0x18 + local_20 * 4), iVar1 != 0)) &&
       (*(char *)(*(int *)(iVar1 + 8) + 0x78) != '\0')) {
      local_2c = 1;
      local_1c[0] = local_20;
      local_1c[1] = 0;
      local_1c[2] = 0;
      local_1c[3] = 0;
      local_1c[4] = 0;
      local_28 = 1 << ((byte)local_20 & 0x1f) | local_28;
      local_24 = local_20;
      while (local_24 = local_24 + 1, local_24 < 5) {
        if ((((1 << ((byte)local_24 & 0x1f) & local_28) == 0) &&
            (iVar2 = *(int *)(param_1 + 0x18 + local_24 * 4), iVar2 != 0)) &&
           (*(int *)(iVar1 + 8) == *(int *)(iVar2 + 8))) {
          local_1c[local_2c] = local_24;
          local_2c = local_2c + 1;
          local_28 = 1 << ((byte)local_24 & 0x1f) | local_28;
        }
      }
      for (local_30 = 0; local_30 < local_2c; local_30 = local_30 + 1) {
        iVar1 = *(int *)(param_1 + 0x18 + local_1c[local_30] * 4);
        *(int *)(iVar1 + 0xb4) = local_30;
        *(int *)(iVar1 + 0xb8) = local_2c;
      }
    }
  }
  FUN_0083e885();
  return;
}

