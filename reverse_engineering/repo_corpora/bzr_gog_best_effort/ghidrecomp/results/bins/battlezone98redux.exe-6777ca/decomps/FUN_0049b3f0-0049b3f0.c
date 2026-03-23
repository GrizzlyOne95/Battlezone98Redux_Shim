
undefined4 * __fastcall FUN_0049b3f0(undefined4 *param_1)

{
  FUN_004d4980();
  *param_1 = ColorFade::vftable;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) & 0xfd;
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) & 0xfb;
  return param_1;
}

