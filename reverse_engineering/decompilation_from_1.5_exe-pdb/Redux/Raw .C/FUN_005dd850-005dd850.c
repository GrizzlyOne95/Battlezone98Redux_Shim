
undefined4 * __fastcall FUN_005dd850(undefined4 *param_1)

{
  FUN_0047ff00();
  *param_1 = SupplyDepotClass::vftable;
  param_1[5] = 0x53444550;
  param_1[6] = "supplydepot";
  param_1[0x4f] = 0x41;
  param_1[0x50] = 0x45;
  param_1[0x58] = 0x41f00000;
  param_1[0x59] = 0x3f800000;
  param_1[0x5a] = 100;
  strncpy((char *)(param_1 + 0x5b),"weapon.wav",0x10);
  return param_1;
}

