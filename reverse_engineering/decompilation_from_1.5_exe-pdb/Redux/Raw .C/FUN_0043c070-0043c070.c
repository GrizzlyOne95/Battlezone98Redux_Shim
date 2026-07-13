
int FUN_0043c070(int param_1)

{
  int iVar1;
  int local_c;
  int local_8;
  
  local_8 = *(int *)(param_1 + 100);
  local_c = 0;
  while (((&DAT_0260c2e8)[local_8 * 4] != -1 && (local_c < 0x65))) {
    local_8 = (&DAT_0260c2e8)[local_8 * 4];
    local_c = local_c + 1;
  }
  iVar1 = (&DAT_0260c2f0)[local_8 * 4];
  local_c = 0;
  while ((local_8 != -1 && (local_c < 0x65))) {
    (&DAT_0260c2f0)[local_8 * 4] = iVar1 + 1;
    local_8 = (&DAT_0260c2ec)[local_8 * 4];
    local_c = local_c + 1;
  }
  return iVar1 + 1;
}

