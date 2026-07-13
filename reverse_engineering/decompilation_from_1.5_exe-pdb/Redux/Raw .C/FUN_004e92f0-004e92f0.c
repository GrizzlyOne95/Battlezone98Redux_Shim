
undefined4 * __fastcall FUN_004e92f0(undefined4 *param_1)

{
  FUN_005ab2c0();
  *param_1 = HealthPowerupClass::vftable;
  param_1[5] = 0x524b4954;
  param_1[6] = "repairkit";
  strncpy((char *)(param_1 + 0x54),"repair.wav",0x10);
  param_1[0x5c] = 0x447a0000;
  return param_1;
}

