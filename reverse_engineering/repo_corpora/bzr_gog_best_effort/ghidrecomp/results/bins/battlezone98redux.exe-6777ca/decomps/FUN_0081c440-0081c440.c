
undefined4 __thiscall FUN_0081c440(int *param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  bool bVar2;
  uint local_34;
  uint local_30;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  byte *local_18;
  int local_10;
  
  for (local_10 = 0; local_10 < *param_1; local_10 = local_10 + 1) {
    local_1c = (byte *)(param_1 + local_10 * 0x81 + 1);
    local_18 = param_3;
    do {
      bVar1 = *local_18;
      bVar2 = bVar1 < *local_1c;
      if (bVar1 != *local_1c) {
LAB_0081c4b9:
        local_30 = -(uint)bVar2 | 1;
        goto LAB_0081c4c1;
      }
      if (bVar1 == 0) break;
      bVar1 = local_18[1];
      bVar2 = bVar1 < local_1c[1];
      if (bVar1 != local_1c[1]) goto LAB_0081c4b9;
      local_18 = local_18 + 2;
      local_1c = local_1c + 2;
    } while (bVar1 != 0);
    local_30 = 0;
LAB_0081c4c1:
    if (local_30 == 0) {
      return 0;
    }
  }
  local_10 = 0;
  do {
    if (*param_1 <= local_10) {
      return 0;
    }
    local_24 = (byte *)(param_1 + local_10 * 0x81 + 0x41);
    local_20 = param_2;
    do {
      bVar1 = *local_20;
      bVar2 = bVar1 < *local_24;
      if (bVar1 != *local_24) {
LAB_0081c550:
        local_34 = -(uint)bVar2 | 1;
        goto LAB_0081c558;
      }
      if (bVar1 == 0) break;
      bVar1 = local_20[1];
      bVar2 = bVar1 < local_24[1];
      if (bVar1 != local_24[1]) goto LAB_0081c550;
      local_20 = local_20 + 2;
      local_24 = local_24 + 2;
    } while (bVar1 != 0);
    local_34 = 0;
LAB_0081c558:
    if (local_34 == 0) {
      if (param_1[local_10 * 0x81 + 0x81] != 0) {
        return 0;
      }
      local_2c = param_3;
      local_28 = (byte *)(param_1 + local_10 * 0x81 + 1);
      do {
        bVar1 = *local_2c;
        *local_28 = bVar1;
        local_2c = local_2c + 1;
        local_28 = local_28 + 1;
      } while (bVar1 != 0);
      return 1;
    }
    local_10 = local_10 + 1;
  } while( true );
}

