
uint FUN_0062be60(uint param_1)

{
  uint *local_c;
  uint local_8;
  
  if ((0xd < param_1) || ((&DAT_008ec7a0)[param_1 * 0xd] != param_1)) {
    local_c = &DAT_008ec7a0;
    for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
      if (*local_c == param_1) {
        return local_8;
      }
      local_c = local_c + 0xd;
    }
    param_1 = 0;
  }
  return param_1;
}

