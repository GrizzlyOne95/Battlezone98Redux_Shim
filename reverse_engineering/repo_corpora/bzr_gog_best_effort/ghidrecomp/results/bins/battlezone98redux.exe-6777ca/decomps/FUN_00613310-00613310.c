
undefined4 * __fastcall FUN_00613310(undefined4 *param_1)

{
  FUN_005ab2c0();
  *param_1 = WeaponPowerupClass::vftable;
  param_1[5] = 0x5745504e;
  param_1[6] = "wpnpower";
  strncpy((char *)(param_1 + 0x54),"weapon.wav",0x10);
  param_1[0x5c] = 0;
  return param_1;
}

