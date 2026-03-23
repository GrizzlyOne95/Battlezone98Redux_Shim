
undefined4 * FUN_0062f130(void)

{
  undefined4 *puVar1;
  undefined1 local_14 [12];
  undefined4 *local_8;
  
  local_8 = malloc(0x14);
  if (local_8 == (undefined4 *)0x0) {
    local_8 = (undefined4 *)0x0;
  }
  else {
    puVar1 = (undefined4 *)FUN_00440000(local_14,0,0x3f490fdb,0);
    *local_8 = *puVar1;
    local_8[1] = puVar1[1];
    local_8[2] = puVar1[2];
    local_8[3] = 400;
    local_8[4] = 400;
  }
  return local_8;
}

