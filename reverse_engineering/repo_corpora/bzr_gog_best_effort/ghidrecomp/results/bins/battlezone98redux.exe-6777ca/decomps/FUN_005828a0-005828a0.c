
undefined4 * __fastcall FUN_005828a0(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = ObjectLobberClass::vftable;
  param_1[3] = 0x4c4f4242;
  param_1[4] = "lobber";
  param_1[0x20] = 0x3f800000;
  param_1[0x21] = 0x42c80000;
  strncpy((char *)(param_1 + 0x16),"wcbl.wav",0x10);
  return param_1;
}

