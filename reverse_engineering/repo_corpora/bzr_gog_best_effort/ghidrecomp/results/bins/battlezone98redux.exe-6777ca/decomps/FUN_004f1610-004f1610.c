
undefined4 * __fastcall FUN_004f1610(undefined4 *param_1)

{
  int local_c;
  
  FUN_004e53a0();
  *param_1 = HuntTask::vftable;
  param_1[0x53] = 0;
  param_1[0x59] = 0;
  for (local_c = 0; local_c < 5; local_c = local_c + 1) {
    param_1[local_c + 0x54] = 0xbf800000;
  }
  return param_1;
}

