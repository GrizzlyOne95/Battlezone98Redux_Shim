
int * FUN_0062c700(int param_1,int param_2,short param_3)

{
  int *piVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (DAT_00920c7c <= local_8) {
      return (int *)0x0;
    }
    piVar1 = (int *)(&DAT_02a1f570 + local_8 * 0xe4);
    if ((((*piVar1 != 0) && ((uint)*(ushort *)(&DAT_02a1f574 + local_8 * 0xe4) == (int)param_3)) &&
        (*(int *)(*piVar1 + 8) == param_1)) && (*(int *)(*piVar1 + 0xc) == param_2)) break;
    local_8 = local_8 + 1;
  }
  return piVar1;
}

