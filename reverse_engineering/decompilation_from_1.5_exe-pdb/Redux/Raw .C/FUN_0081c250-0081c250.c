
int __thiscall FUN_0081c250(int *param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_28;
  uint local_24;
  byte *local_1c;
  byte *local_18;
  byte *local_14;
  byte *local_10;
  int local_c;
  
  local_c = 0;
  do {
    if (*param_1 <= local_c) {
      FUN_007d65d0("BattleZone (input_config) get_key Error!");
      return -1;
    }
    local_14 = (byte *)(param_1 + local_c * 0x81 + 0x41);
    local_10 = param_2;
    do {
      bVar1 = *local_10;
      bVar2 = bVar1 < *local_14;
      if (bVar1 != *local_14) {
LAB_0081c2d0:
        local_24 = -(uint)bVar2 | 1;
        goto LAB_0081c2d8;
      }
      if (bVar1 == 0) break;
      bVar1 = local_10[1];
      bVar2 = bVar1 < local_14[1];
      if (bVar1 != local_14[1]) goto LAB_0081c2d0;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (bVar1 != 0);
    local_24 = 0;
LAB_0081c2d8:
    if (local_24 == 0) {
      local_1c = &DAT_00874be8;
      local_18 = (byte *)(param_1 + local_c * 0x81 + 1);
      break;
    }
    local_c = local_c + 1;
  } while( true );
  while( true ) {
    bVar1 = local_18[1];
    bVar2 = bVar1 < local_1c[1];
    if (bVar1 != local_1c[1]) goto LAB_0081c339;
    local_18 = local_18 + 2;
    local_1c = local_1c + 2;
    if (bVar1 == 0) break;
    bVar1 = *local_18;
    bVar2 = bVar1 < *local_1c;
    if (bVar1 != *local_1c) {
LAB_0081c339:
      local_28 = -(uint)bVar2 | 1;
      goto LAB_0081c341;
    }
    if (bVar1 == 0) break;
  }
  local_28 = 0;
LAB_0081c341:
  if (local_28 == 0) {
    local_c = -1;
  }
  return local_c;
}

