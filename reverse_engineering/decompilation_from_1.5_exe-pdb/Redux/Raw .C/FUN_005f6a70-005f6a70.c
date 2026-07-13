
undefined4 * __fastcall FUN_005f6a70(undefined4 *param_1)

{
  FUN_005f9350();
  *param_1 = TurretTankProcess::vftable;
  param_1[0xc] = 0;
  *(undefined1 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x19) = 0;
  return param_1;
}

