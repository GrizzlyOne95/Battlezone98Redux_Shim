
undefined4 * __fastcall FUN_0047be40(undefined4 *param_1)

{
  FUN_0048f860();
  *param_1 = BeamGunClass::vftable;
  param_1[3] = 0x4247554e;
  param_1[4] = "beamgun";
  strncpy((char *)(param_1 + 0x16),"wlflame.wav",0x10);
  return param_1;
}

