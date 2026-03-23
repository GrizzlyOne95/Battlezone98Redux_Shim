
undefined4 * __fastcall FUN_005a7240(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = PopperGunClass::vftable;
  param_1[3] = 0x504f5047;
  param_1[4] = "poppergun";
  strncpy((char *)(param_1 + 0x16),"wcbl.wav",0x10);
  param_1[0x20] = 0x3f800000;
  param_1[0x21] = 0x3f800000;
  return param_1;
}

