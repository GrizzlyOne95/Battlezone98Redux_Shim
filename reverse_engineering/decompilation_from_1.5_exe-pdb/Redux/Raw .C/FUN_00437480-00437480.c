
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00437480(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *local_10;
  char *local_c;
  
  local_10 = param_2;
  local_c = &DAT_02cecf08;
  do {
    cVar1 = *local_10;
    *local_c = cVar1;
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  DAT_02cecefc = &DAT_00915578;
  _DAT_0091557c = param_1;
  iVar2 = FUN_0043fe20(&DAT_02cecee0,param_2,&DAT_02cecf08);
  if (iVar2 == 0) {
    FUN_007d64a0("Failed to init 3D hardware acceleration");
  }
  return;
}

