
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0058d3c0(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int local_8;
  
  if (DAT_00918140 == 0) {
    _DAT_00918160 = param_1;
  }
  local_8 = 0;
  while( true ) {
    iVar1 = DAT_00918140;
    if (DAT_00918140 <= local_8) {
      DAT_00918140 = DAT_00918140 + 1;
      piVar2 = (int *)FUN_005924d0(iVar1);
      *piVar2 = param_2;
      return;
    }
    piVar2 = (int *)FUN_005924d0(local_8);
    if (*piVar2 == param_2) break;
    local_8 = local_8 + 1;
  }
  return;
}

