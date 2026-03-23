
undefined4 * __fastcall FUN_004d2a50(undefined4 *param_1)

{
  FUN_00511690();
  *param_1 = FlareMineClass::vftable;
  param_1[5] = 0x464c4152;
  param_1[6] = "flare";
  param_1[0x58] = 0x42700000;
  param_1[0x5a] = 0;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  param_1[0x60] = 0x3d4ccccd;
  param_1[0x61] = 0x3f000000;
  return param_1;
}

