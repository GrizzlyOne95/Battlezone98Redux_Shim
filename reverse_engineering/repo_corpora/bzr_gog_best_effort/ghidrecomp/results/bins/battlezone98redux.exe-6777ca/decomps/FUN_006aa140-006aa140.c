
undefined4 * __fastcall FUN_006aa140(undefined4 *param_1)

{
  *param_1 = CCallbackBase::vftable;
  *(undefined1 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  return param_1;
}

