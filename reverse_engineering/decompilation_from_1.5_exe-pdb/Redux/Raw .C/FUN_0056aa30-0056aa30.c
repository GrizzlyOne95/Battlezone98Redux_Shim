
undefined4 * __fastcall FUN_0056aa30(undefined4 *param_1)

{
  FUN_005be1b0();
  *param_1 = MissileClass::vftable;
  param_1[3] = 0x4d53534c;
  param_1[4] = "missile";
  *(undefined1 *)((int)param_1 + 0x5e) = 1;
  param_1[0x13] = 10;
  param_1[0x34] = 0x3f800000;
  param_1[0x35] = 0x42c80000;
  return param_1;
}

