
undefined4 * __fastcall FUN_004908a0(undefined4 *param_1)

{
  FUN_0048f860();
  *param_1 = ChargeGunClass::vftable;
  param_1[3] = 0x43485247;
  param_1[4] = "chargegun";
  strncpy((char *)(param_1 + 0x16),"wlflame.wav",0x10);
  param_1[0x26] = 0x462c4400;
  param_1[0x27] = 0x457a0000;
  param_1[0x28] = 0x42c80000;
  param_1[0x29] = 0;
  param_1[0x2a] = 1;
  param_1[0x2b] = 0;
  return param_1;
}

