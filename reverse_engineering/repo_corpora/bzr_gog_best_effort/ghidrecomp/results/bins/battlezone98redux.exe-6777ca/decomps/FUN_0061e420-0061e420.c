
undefined ** FUN_0061e420(char *param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x6e < local_8) {
      return (undefined **)0x0;
    }
    iVar1 = _stricmp((&PTR_s_cmd_x_008eb1e8)[local_8 * 8],param_1);
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  return &PTR_s_cmd_x_008eb1e8 + local_8 * 8;
}

