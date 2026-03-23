
undefined4 * __fastcall FUN_005dacf0(undefined4 *param_1)

{
  FUN_004e7f60();
  *param_1 = SprayBombClass::vftable;
  param_1[3] = 0x53424d42;
  param_1[4] = "spraybomb";
  param_1[0x34] = 0;
  param_1[0x35] = 0x3f000000;
  strncpy((char *)(param_1 + 0x36),"bounce.wav",0x10);
  return param_1;
}

