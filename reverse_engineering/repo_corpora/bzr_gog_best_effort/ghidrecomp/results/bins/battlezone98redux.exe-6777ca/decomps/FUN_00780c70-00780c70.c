
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00780c70(undefined4 *param_1)

{
  if ((DAT_008eaad8 != DAT_02c06770) || (DAT_009454bc != DAT_02c06774)) {
    FUN_00780800(DAT_008eaad8);
  }
  DAT_02cc50ec = param_1;
  DAT_02cc50f0 = 0;
  _DAT_02cc50e8 = 1;
  _DAT_02cc50f8 = (float)*(double *)(param_1 + 0x58) * DAT_02cc50e4;
  _DAT_02cc5100 = (float)*(double *)(param_1 + 0x5c) * DAT_02cc50e4;
  _DAT_02cc50fc = (float)*(double *)(param_1 + 0x5a) * 10.0;
  if (DAT_008eaad8 == 3) {
    FUN_00782c20(param_1);
  }
  else if (DAT_009454ac == 0) {
    if ((param_1 == &DAT_008eaae0) && (DAT_009454bc != 0)) {
      FUN_007829b0(&DAT_008eaae0);
      DAT_009454bc = 0;
      DAT_02cd9980 = 1;
    }
    else {
      FUN_00782ee0(param_1);
    }
  }
  else {
    FUN_00782650(param_1);
  }
  FUN_007753c0(param_1);
  return;
}

