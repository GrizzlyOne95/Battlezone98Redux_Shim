
undefined4 * __fastcall FUN_00582b60(undefined4 *param_1)

{
  FUN_005f9350();
  *param_1 = OffensiveProcess::vftable;
  *(undefined1 *)(param_1 + 0x17) = 1;
  param_1[0x1a] = 0x471c4000;
  param_1[0x1b] = 0x46742400;
  param_1[0x1c] = 0x471c4000;
  param_1[0x1d] = 0x41f00000;
  param_1[0xc] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  return param_1;
}

