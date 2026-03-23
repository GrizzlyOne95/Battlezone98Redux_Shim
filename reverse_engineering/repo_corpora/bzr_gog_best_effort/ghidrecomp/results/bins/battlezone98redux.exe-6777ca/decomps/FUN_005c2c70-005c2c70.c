
undefined4 * __fastcall FUN_005c2c70(undefined4 *param_1)

{
  FUN_004efca0();
  *param_1 = ScavengerClass::vftable;
  param_1[5] = 0x53434156;
  param_1[6] = "scavenger";
  param_1[0x4f] = 0x19;
  param_1[0x50] = 0x22;
  param_1[0x17c] = 3;
  strncpy((char *)(param_1 + 0x17d),"suck.wav",0x10);
  *(undefined1 *)(param_1 + 0x181) = 0;
  *(undefined1 *)(param_1 + 0x185) = 0;
  *(undefined1 *)(param_1 + 0x189) = 0;
  *(undefined1 *)(param_1 + 0x18d) = 0;
  return param_1;
}

