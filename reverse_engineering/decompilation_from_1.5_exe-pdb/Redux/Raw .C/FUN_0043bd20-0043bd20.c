
void FUN_0043bd20(void)

{
  uint local_c;
  undefined4 *local_8;
  
  local_8 = &DAT_0260c2e8;
  for (local_c = 0; local_c < 100; local_c = local_c + 1) {
    *local_8 = 0xffffffff;
    local_8[1] = local_c - 1;
    local_8[2] = 0;
    local_8[3] = 0;
    local_8 = local_8 + 4;
  }
  DAT_0260c2e4 = local_c - 1;
  DAT_0260c254 = local_c;
  DAT_0260c928 = local_c;
  return;
}

