
void FUN_00782ef0(ushort *param_1,int param_2)

{
  int local_c;
  int local_8;
  
  local_8 = (int)(*param_1 & 0xf000) >> 0xc;
  local_c = 0;
  while( true ) {
    if (7 < local_c) {
      return;
    }
    local_8 = local_8 + param_2;
    if (7 < local_8) {
      local_8 = 0;
    }
    if (local_8 < 0) {
      local_8 = 7;
    }
    if ((&DAT_02c06778)[local_8 * 0x48] != '\0') break;
    local_c = local_c + 1;
  }
  *param_1 = *param_1 & 0x7c | (ushort)(local_8 << 0xc) | (ushort)(local_8 << 8) & 0xf00;
  return;
}

