
bool FUN_00820e00(char *param_1)

{
  bool bVar1;
  int iVar2;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (DAT_00946730 <= local_8) {
      bVar1 = DAT_00946730 < 0x800;
      if (bVar1) {
        memset(&DAT_02c41b08 + DAT_00946730 * 0x100,0,0x100);
        iVar2 = DAT_00946730 * 0x100;
        DAT_00946730 = DAT_00946730 + 1;
        strncpy(&DAT_02c41b08 + iVar2,param_1,0xff);
      }
      return bVar1;
    }
    iVar2 = _stricmp(&DAT_02c41b08 + local_8 * 0x100,param_1);
    if (iVar2 == 0) break;
    local_8 = local_8 + 1;
  }
  return false;
}

