
undefined4 * __fastcall FUN_004f8a90(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = LauncherClass::vftable;
  param_1[3] = 0x4c4e4348;
  param_1[4] = "launcher";
  strncpy((char *)(param_1 + 0x16),"wrock.wav",0x10);
  param_1[0x20] = 0;
  param_1[0xd] = 0;
  param_1[0x21] = 0x3f800000;
  param_1[0x22] = 0x40a00000;
  param_1[0x23] = 0x3fc90fdb;
  param_1[0x29] = param_1[0x1a];
  *(undefined1 *)(param_1 + 0x2a) = 0;
  param_1[0x24] = param_1[0x1a];
  *(undefined1 *)(param_1 + 0x25) = 0;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  return param_1;
}

