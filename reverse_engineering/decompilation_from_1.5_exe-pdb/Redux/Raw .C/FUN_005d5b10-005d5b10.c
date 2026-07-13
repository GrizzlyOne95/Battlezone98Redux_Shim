
undefined4 * __fastcall FUN_005d5b10(undefined4 *param_1)

{
  FUN_0048f860();
  *param_1 = SniperGunClass::vftable;
  param_1[3] = 0x534e4950;
  param_1[4] = "snipergun";
  *(undefined1 *)((int)param_1 + 0x79) = 0;
  return param_1;
}

