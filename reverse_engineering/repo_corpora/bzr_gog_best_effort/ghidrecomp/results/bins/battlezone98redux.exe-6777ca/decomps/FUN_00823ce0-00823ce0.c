
undefined4 * FUN_00823ce0(void)

{
  undefined4 *local_8;
  
  local_8 = DAT_02cc1b40;
  while( true ) {
    if (local_8 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if ((*(uint *)(local_8[2] + 0x120) & 0x100) != 0) break;
    local_8 = (undefined4 *)*local_8;
  }
  return local_8;
}

