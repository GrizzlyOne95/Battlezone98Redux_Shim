
undefined4 * __fastcall FUN_004e7f60(undefined4 *param_1)

{
  FUN_005be1b0();
  *param_1 = GrenadeClass::vftable;
  param_1[3] = 0x4752454e;
  param_1[4] = "grenade";
  *(undefined1 *)((int)param_1 + 0x5e) = 1;
  param_1[0x13] = 10;
  param_1[0x14] = 0x7149f2ca;
  param_1[0x16] = 0x43fa0000;
  *(undefined2 *)(param_1 + 0x17) = 2;
  param_1[0x15] = 0x42480000;
  return param_1;
}

