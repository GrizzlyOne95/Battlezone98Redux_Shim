
undefined4 * __fastcall FUN_005b8a90(undefined4 *param_1)

{
  FUN_0056b320();
  *param_1 = RemoteDetonatorClass::vftable;
  param_1[4] = "detonator";
  param_1[3] = 0x52444554;
  param_1[0x26] = param_1[0x1a];
  return param_1;
}

