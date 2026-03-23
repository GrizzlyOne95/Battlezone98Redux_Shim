
undefined4 * __fastcall FUN_005df230(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = TargetingGunClass::vftable;
  param_1[3] = 0x54524754;
  param_1[4] = "targeting";
  strncpy((char *)(param_1 + 0x16),"whmgun.wav",0x10);
  strncpy((char *)(param_1 + 0x20),"h45ch.wav",0x10);
  param_1[0x24] = 0;
  param_1[0x25] = 0x3f800000;
  param_1[0x26] = 0x3f800000;
  param_1[0x27] = 0x3e4ccccd;
  param_1[0x28] = 10;
  param_1[0x2a] = 0;
  param_1[0x2b] = 0;
  return param_1;
}

