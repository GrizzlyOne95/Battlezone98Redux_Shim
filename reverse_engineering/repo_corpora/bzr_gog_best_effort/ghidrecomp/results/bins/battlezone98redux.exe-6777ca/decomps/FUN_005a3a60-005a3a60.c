
undefined4 * __fastcall FUN_005a3a60(undefined4 *param_1)

{
  FUN_00582b60();
  *param_1 = PersonProcess::vftable;
  param_1[8] = 3;
  *(undefined1 *)(param_1 + 0x1f) = 0;
  param_1[0x20] = 0;
  return param_1;
}

