
undefined * FUN_0062d8d0(int param_1,int param_2)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_0062d660(param_1,param_2);
  local_8 = *(int *)(&DAT_02b3c730 + iVar1 * 4);
  while( true ) {
    if (local_8 == -1) {
      return (undefined *)0x0;
    }
    if ((*(int *)(&DAT_02b40918 + local_8 * 0x34) == param_1) &&
       (*(int *)(&DAT_02b4091c + local_8 * 0x34) == param_2)) break;
    local_8 = *(int *)(&DAT_02b40948 + local_8 * 0x34);
  }
  return &DAT_02b40918 + local_8 * 0x34;
}

