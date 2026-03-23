
undefined4 * __fastcall FUN_005d6a70(undefined4 *param_1)

{
  FUN_00481220();
  *param_1 = SniperShellClass::vftable;
  param_1[3] = 0x534e4950;
  param_1[4] = "snipershell";
  param_1[0x1e] = 0x40400000;
  param_1[0x1f] = 0x3f800000;
  return param_1;
}

