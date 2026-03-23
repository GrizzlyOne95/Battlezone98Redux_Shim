
undefined4 * __fastcall FUN_00660c60(undefined4 *param_1)

{
  FUN_0047ff00();
  *param_1 = PortalClass::vftable;
  param_1[5] = 0x504f5254;
  param_1[6] = "portal";
  param_1[0x4f] = 0x5a;
  param_1[0x50] = 0x5a;
  param_1[0x58] = 0x3f800000;
  *(undefined1 *)(param_1 + 0x59) = 0;
  return param_1;
}

