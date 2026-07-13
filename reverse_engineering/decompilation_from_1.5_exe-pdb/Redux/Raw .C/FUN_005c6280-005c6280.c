
undefined4 * __thiscall FUN_005c6280(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint local_c;
  
  FUN_005a79f0(param_2,param_3);
  *param_1 = ScrapDropoff::vftable;
  param_1[6] = ScrapDropoff::vftable;
  local_c = 0;
  while( true ) {
    if (0x13 < local_c) {
      return param_1;
    }
    if ((*(int *)(&DAT_009181c0 + local_c * 8) == 0) && (*(int *)(&DAT_009181c4 + local_c * 8) == 0)
       ) break;
    local_c = local_c + 1;
  }
  *(undefined4 **)(&DAT_009181c0 + local_c * 8) = param_1;
  return param_1;
}

