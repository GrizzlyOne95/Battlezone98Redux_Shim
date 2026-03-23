
undefined * FUN_006d15a0(uint param_1)

{
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x15 < local_8) {
      return PTR_DAT_008fe820;
    }
    if (param_1 < *(uint *)(&DAT_008fe7c8 + local_8 * 4)) break;
    local_8 = local_8 + 1;
  }
  return *(undefined **)(&DAT_008fe7c8 + local_8 * 4);
}

