
undefined4 * __fastcall FUN_005ab2c0(undefined4 *param_1)

{
  FUN_004e0190();
  *param_1 = PowerUpClass::vftable;
  param_1[5] = 0x50575550;
  param_1[6] = "powerup";
  param_1[7] = 3;
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x58) = 0;
  return param_1;
}

