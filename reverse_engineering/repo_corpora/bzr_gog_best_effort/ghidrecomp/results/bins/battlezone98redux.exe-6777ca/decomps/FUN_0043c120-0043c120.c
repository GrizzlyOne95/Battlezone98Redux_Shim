
int FUN_0043c120(int param_1)

{
  int local_10;
  int local_c;
  int local_8;
  
  local_c = *(int *)(param_1 + 100);
  local_8 = 0;
  while (((&DAT_0260c2e8)[local_c * 4] != -1 && (local_8 < 0x65))) {
    local_c = (&DAT_0260c2e8)[local_c * 4];
    local_8 = local_8 + 1;
  }
  local_10 = 0;
  local_8 = 0;
  while ((local_c != -1 && (local_8 < 0x65))) {
    local_10 = local_10 + 1;
    local_c = (&DAT_0260c2ec)[local_c * 4];
    local_8 = local_8 + 1;
  }
  return local_10;
}

