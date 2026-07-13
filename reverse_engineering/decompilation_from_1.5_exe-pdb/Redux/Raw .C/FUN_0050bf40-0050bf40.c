
undefined4 * __fastcall FUN_0050bf40(undefined4 *param_1)

{
  FUN_0048f860();
  *param_1 = MachineGunClass::vftable;
  param_1[3] = 0x4d47554e;
  param_1[4] = "machinegun";
  param_1[0x20] = 0x3e4ccccd;
  strncpy((char *)(param_1 + 0x16),"wlmgun.wav",0x10);
  return param_1;
}

