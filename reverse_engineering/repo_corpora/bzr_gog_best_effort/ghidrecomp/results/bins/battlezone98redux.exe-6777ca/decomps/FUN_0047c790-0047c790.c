
undefined4 * __fastcall FUN_0047c790(undefined4 *param_1)

{
  FUN_00481220();
  *param_1 = BoltClass::vftable;
  param_1[3] = 0x424f4c54;
  param_1[4] = &DAT_00876558;
  param_1[0x13] = 10;
  param_1[0x14] = 0x3f800000;
  param_1[0x16] = 0x42c80000;
  *(undefined2 *)(param_1 + 0x17) = 1;
  param_1[0x15] = 0x43480000;
  param_1[0x1e] = 0x3dcccccd;
  param_1[0x1f] = 0x40000000;
  param_1[0x20] = 0x3f000000;
  param_1[0x22] = 0x3dcccccd;
  return param_1;
}

