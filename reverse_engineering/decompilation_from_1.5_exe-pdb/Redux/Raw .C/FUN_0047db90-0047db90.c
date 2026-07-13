
undefined4 * __fastcall FUN_0047db90(undefined4 *param_1)

{
  FUN_004e7f60();
  *param_1 = BounceBombClass::vftable;
  param_1[3] = 0x42424d42;
  param_1[4] = "bouncebomb";
  param_1[0x34] = 0x3f000000;
  strncpy((char *)(param_1 + 0x35),"bounce.wav",0x10);
  return param_1;
}

