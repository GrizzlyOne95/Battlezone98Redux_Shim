
undefined4 * __fastcall FUN_005e5080(undefined4 *param_1)

{
  FUN_005ab2c0();
  *param_1 = TorpedoClass::vftable;
  param_1[5] = 0x544f5250;
  param_1[6] = "torpedo";
  param_1[0x14] = 0;
  param_1[0x5c] = 0x3f800000;
  param_1[0x5d] = 0x41a00000;
  param_1[0x5e] = 0x40a00000;
  param_1[0x5f] = 0x41c80000;
  param_1[0x60] = 0x41200000;
  param_1[0x61] = 0x3f800000;
  param_1[0x62] = 0x40a00000;
  param_1[99] = 0x42700000;
  param_1[100] = 0;
  *(undefined2 *)(param_1 + 0x65) = 0;
  param_1[0x66] = 0;
  *(undefined1 *)(param_1 + 0x67) = 0;
  return param_1;
}

