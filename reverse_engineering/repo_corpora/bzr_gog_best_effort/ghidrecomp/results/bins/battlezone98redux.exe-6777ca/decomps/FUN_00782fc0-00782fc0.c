
void FUN_00782fc0(ushort *param_1,int param_2)

{
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = (int)(*param_1 & 0xf000) >> 0xc;
  local_8 = (int)(*param_1 & 0xf00) >> 8;
  local_10 = 0;
  do {
    if (7 < local_10) {
      return;
    }
    for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
      local_8 = local_8 + param_2;
      if (7 < local_8) {
        local_8 = 0;
      }
      if (local_8 < 0) {
        local_8 = 7;
      }
      if (((&DAT_02c06778)[local_8 * 8 + local_c * 0x40] != '\0') && (local_c != local_8)) {
        *param_1 = *param_1 & 0x7c | (ushort)(local_c << 0xc) | (ushort)(local_8 << 8) & 0xf00;
        return;
      }
    }
    local_c = local_c + param_2;
    if (7 < local_c) {
      local_c = 0;
    }
    if (local_c < 0) {
      local_c = 7;
    }
    local_10 = local_10 + 1;
  } while( true );
}

