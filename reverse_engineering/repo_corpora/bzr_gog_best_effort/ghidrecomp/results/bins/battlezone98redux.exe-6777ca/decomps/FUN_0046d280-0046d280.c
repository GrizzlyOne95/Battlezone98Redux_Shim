
undefined4 * __fastcall FUN_0046d280(undefined4 *param_1)

{
  FUN_005ab2c0();
  *param_1 = AmmoPowerupClass::vftable;
  param_1[5] = 0x414d4d4f;
  param_1[6] = "ammopack";
  strncpy((char *)(param_1 + 0x54),"weapon.wav",0x10);
  param_1[0x5c] = 500;
  return param_1;
}

