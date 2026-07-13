
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046eed0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int local_10;
  int local_c;
  uint local_8;
  
  _DAT_0260d6c0 = param_1;
  _DAT_0260d63c = param_2;
  DAT_0260d630 = param_3;
  DAT_0260d6d4 = param_4;
  DAT_0260d638 = param_5;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    for (local_10 = 0; local_10 < 0x10; local_10 = local_10 + 1) {
      *(undefined4 *)(&DAT_0260d640 + local_10 * 4 + local_c * 0x40) = 0;
    }
  }
  for (local_8 = 0; (int)local_8 < 0x10; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_0260d6d8 + local_8 * 4) = 0;
    if (0xf < local_8) {
      ___report_rangecheckfailure();
    }
    (&DAT_0260d6c4)[local_8] = 0;
  }
  DAT_0260d111 = 1;
  return;
}

