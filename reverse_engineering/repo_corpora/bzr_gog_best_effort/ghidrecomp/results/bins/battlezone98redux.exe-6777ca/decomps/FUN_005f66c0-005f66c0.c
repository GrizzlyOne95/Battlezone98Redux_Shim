
undefined4 * __fastcall FUN_005f66c0(undefined4 *param_1)

{
  FUN_004efca0();
  *param_1 = TurretTankClass::vftable;
  param_1[5] = 0x54544e4b;
  param_1[6] = "turrettank";
  param_1[0x4f] = 0xf;
  param_1[0x50] = 0x18;
  param_1[0x17c] = 0x40000000;
  param_1[0x17d] = 0x40a00000;
  param_1[0x17e] = 0x40a00000;
  return param_1;
}

