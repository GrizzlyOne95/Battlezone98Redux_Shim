
undefined4 * __fastcall FUN_006607c0(undefined4 *param_1)

{
  FUN_004d4980();
  *param_1 = PortalBlob::vftable;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) | 1;
  return param_1;
}

