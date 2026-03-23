
undefined4 * __fastcall FUN_006122e0(undefined4 *param_1)

{
  FUN_00511690();
  *param_1 = WeaponMineClass::vftable;
  param_1[5] = 0x57504e4d;
  param_1[6] = "weaponmine";
  param_1[0x16] = 1000;
  param_1[0x58] = 0x7149f2ca;
  param_1[0x5a] = 0x42480000;
  param_1[0x5b] = 0x41200000;
  param_1[0x5c] = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  return param_1;
}

