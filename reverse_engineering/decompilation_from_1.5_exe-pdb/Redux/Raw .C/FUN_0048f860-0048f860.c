
undefined4 * __fastcall FUN_0048f860(undefined4 *param_1)

{
  FUN_006119a0();
  *param_1 = CannonClass::vftable;
  param_1[3] = 0x43414e4e;
  param_1[4] = "cannon";
  *(undefined1 *)((int)param_1 + 0x79) = 1;
  param_1[0x20] = 0x3e4ccccd;
  param_1[0x21] = 1;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  strncpy((char *)(param_1 + 0x16),"h45ch.wav",0x10);
  return param_1;
}

