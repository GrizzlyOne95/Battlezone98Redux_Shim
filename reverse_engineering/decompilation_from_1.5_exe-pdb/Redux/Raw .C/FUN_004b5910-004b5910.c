
undefined4 * __fastcall FUN_004b5910(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = DispenserClass::vftable;
  param_1[3] = 0x44495350;
  param_1[4] = "dispenser";
  strncpy((char *)(param_1 + 0x16),"wwgpl.wav",0x10);
  param_1[0x20] = 0x3f800000;
  return param_1;
}

