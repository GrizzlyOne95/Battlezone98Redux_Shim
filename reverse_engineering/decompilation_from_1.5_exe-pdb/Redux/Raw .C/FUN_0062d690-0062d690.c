
undefined * FUN_0062d690(int param_1)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_0062d630(param_1,0);
  local_8 = *(int *)(&DAT_02b3ee50 + iVar1 * 4);
  while( true ) {
    if (local_8 == -1) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_02b3f018 + local_8 * 0x20) == param_1) break;
    local_8 = *(int *)(&DAT_02b3f034 + local_8 * 0x20);
  }
  return &DAT_02b3f018 + local_8 * 0x20;
}

