
void __fastcall FUN_005c6330(undefined4 *param_1)

{
  uint local_8;
  
  *param_1 = ScrapDropoff::vftable;
  param_1[6] = ScrapDropoff::vftable;
  local_8 = 0;
  do {
    if (0x13 < local_8) {
LAB_005c6388:
      FUN_005a7bf0();
      return;
    }
    if (*(undefined4 **)(&DAT_009181c0 + local_8 * 8) == param_1) {
      *(int *)(&DAT_009181c0 + local_8 * 8) = 0;
      goto LAB_005c6388;
    }
    local_8 = local_8 + 1;
  } while( true );
}

