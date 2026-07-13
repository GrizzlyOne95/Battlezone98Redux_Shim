
void FUN_00442e70(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *local_c;
  undefined4 *local_8;
  
  for (local_8 = DAT_0260cac4; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
    FUN_00442a90(local_8[2]);
  }
  local_8 = DAT_0260cac4;
  puVar1 = local_8;
  while (local_8 = puVar1, local_8 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*local_8;
    local_c = (undefined4 *)*local_8;
    while (local_c != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)*local_c;
      FUN_00443060(local_8[2],local_c[2]);
      local_c = puVar2;
    }
    local_c = DAT_0260d0f0;
    while (local_c != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)*local_c;
      FUN_00443060(local_8[2],local_c[2]);
      local_c = puVar2;
    }
  }
  return;
}

