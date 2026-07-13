
undefined4 * __fastcall FUN_0056b320(undefined4 *param_1)

{
  FUN_0048f860();
  *param_1 = MortarClass::vftable;
  param_1[3] = 0x4d4f5254;
  param_1[4] = "mortar";
  *(undefined1 *)((int)param_1 + 0x79) = 0;
  param_1[0x20] = 0x3f800000;
  strncpy((char *)(param_1 + 0x16),"wcbl.wav",0x10);
  return param_1;
}

