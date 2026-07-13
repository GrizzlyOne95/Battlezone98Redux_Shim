
void __thiscall FUN_006f7480(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  QuickBitSet local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 *local_10;
  uint local_c;
  undefined4 *local_8;
  
  local_8 = param_1;
  if (param_2 < 1) {
    if (param_2 < 0) {
      local_c = -param_2;
LAB_006f7568:
      if ((uint)local_8[2] < local_c) {
        local_c = local_c - local_8[2];
        local_8[6] = local_8[6] - local_8[2];
        if (local_8[4] == local_8[3]) {
          local_8[2] = 0;
          return;
        }
        local_10 = (undefined4 *)local_8[4];
        do {
          if (local_10 == (undefined4 *)local_8[3]) goto LAB_006f7568;
          local_24 = local_10[-2];
          local_20 = local_10[-1];
          local_10 = local_10 + -2;
          local_1c = FUN_006ae390(&local_24);
        } while (local_1c == 0);
        local_8[4] = local_10;
        *local_8 = local_24;
        local_8[1] = local_20;
        local_8[2] = local_1c;
        goto LAB_006f7568;
      }
      local_8[6] = local_8[6] - local_c;
      local_8[2] = local_8[2] - local_c;
    }
  }
  else {
    while( true ) {
      local_14 = FUN_006ae390(local_8);
      local_14 = local_14 - local_8[2];
      if (param_2 < local_14) break;
      param_2 = param_2 - local_14;
      local_8[6] = local_8[6] + local_14;
      local_18 = local_8[4] + 8;
      local_8[4] = local_18;
      if (local_18 == local_8[5]) {
        puVar2 = (undefined4 *)Concurrency::details::QuickBitSet::QuickBitSet(local_2c);
        uVar1 = puVar2[1];
        *local_8 = *puVar2;
        local_8[1] = uVar1;
        local_8[2] = 0;
        return;
      }
      uVar1 = ((undefined4 *)local_8[4])[1];
      *local_8 = *(undefined4 *)local_8[4];
      local_8[1] = uVar1;
      local_8[2] = 0;
    }
    local_8[6] = local_8[6] + param_2;
    local_8[2] = local_8[2] + param_2;
  }
  return;
}

