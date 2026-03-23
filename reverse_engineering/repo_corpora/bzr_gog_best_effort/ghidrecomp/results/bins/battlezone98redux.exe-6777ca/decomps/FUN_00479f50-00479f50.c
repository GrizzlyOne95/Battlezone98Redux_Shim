
undefined4 * __fastcall FUN_00479f50(undefined4 *param_1)

{
  FUN_00481220();
  *param_1 = BeamClass::vftable;
  param_1[3] = 0x4245414d;
  param_1[4] = &DAT_008764a8;
  param_1[0x13] = 10;
  param_1[0x14] = 0x3951b717;
  param_1[0x15] = 0x49742400;
  param_1[0x16] = 0x42c80000;
  *(undefined2 *)(param_1 + 0x17) = 1;
  param_1[0x1e] = 0x3dcccccd;
  param_1[0x1f] = 0x40000000;
  param_1[0x20] = 0x40000000;
  return param_1;
}

