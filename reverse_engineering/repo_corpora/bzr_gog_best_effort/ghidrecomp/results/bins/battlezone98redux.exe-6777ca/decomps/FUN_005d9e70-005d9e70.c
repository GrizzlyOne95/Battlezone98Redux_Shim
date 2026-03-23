
undefined4 * __fastcall FUN_005d9e70(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = SpecialItemClass::vftable;
  param_1[3] = 0x5350434c;
  param_1[4] = "specialitem";
  param_1[0xd] = 100;
  param_1[0x20] = 0x3f800000;
  *(undefined1 *)(param_1 + 0x21) = 0;
  *(undefined1 *)(param_1 + 0x25) = 0;
  param_1[0x29] = 0;
  return param_1;
}

