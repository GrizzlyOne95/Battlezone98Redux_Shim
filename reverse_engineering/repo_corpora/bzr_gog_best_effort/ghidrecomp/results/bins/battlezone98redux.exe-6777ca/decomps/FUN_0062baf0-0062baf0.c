
void FUN_0062baf0(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *local_8;
  
  local_8 = DAT_02a1f498;
  while (local_8 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*local_8;
    uVar2 = local_8[2];
    FUN_008245a0(&DAT_02a1f498,local_8,uVar2);
    DAT_00920c64 = DAT_00920c64 + -1;
    FUN_0062bbb0(uVar2);
    local_8 = puVar1;
  }
  return;
}

