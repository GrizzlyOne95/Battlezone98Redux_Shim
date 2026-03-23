
void FUN_0062bb50(void)

{
  undefined4 *puVar1;
  undefined4 *local_8;
  
  local_8 = DAT_02a1f498;
  while (local_8 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*local_8;
    FUN_008245a0(&DAT_02a1f498,local_8,local_8[2]);
    DAT_00920c64 = DAT_00920c64 + -1;
    local_8 = puVar1;
  }
  return;
}

