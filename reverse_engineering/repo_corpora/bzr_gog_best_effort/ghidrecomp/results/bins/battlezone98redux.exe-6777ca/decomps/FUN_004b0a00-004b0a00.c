
undefined4 * __fastcall FUN_004b0a00(undefined4 *param_1)

{
  FUN_005ab2c0();
  *param_1 = DayWreckerClass::vftable;
  param_1[5] = 0x5752434b;
  param_1[6] = "daywrecker";
  param_1[0x5c] = 0;
  *(undefined2 *)(param_1 + 0x5d) = 0;
  param_1[0x5e] = 0;
  param_1[0x5f] = 0x40a00000;
  return param_1;
}

