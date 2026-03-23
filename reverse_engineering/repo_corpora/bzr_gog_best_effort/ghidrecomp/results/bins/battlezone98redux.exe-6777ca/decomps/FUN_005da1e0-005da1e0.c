
undefined4 * __fastcall FUN_005da1e0(undefined4 *param_1)

{
  FUN_0047ff00();
  *param_1 = SprayBuildingClass::vftable;
  param_1[5] = 0x53424d42;
  param_1[6] = "spraybomb";
  param_1[7] = 5;
  param_1[0x58] = 0;
  *(undefined1 *)(param_1 + 0x59) = 0;
  param_1[0x5d] = 0;
  param_1[0x5e] = 0x3d4ccccd;
  param_1[0x5f] = 0x40000000;
  param_1[0x60] = 0x41200000;
  param_1[0x61] = 0x3e800000;
  return param_1;
}

