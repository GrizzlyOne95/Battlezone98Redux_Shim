
undefined4 * __fastcall FUN_0073a530(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = param_1[1] & 0xff0fffff;
  param_1[1] = param_1[1] & 0xffffff;
  param_1[1] = param_1[1] & 0xfff00000;
  return param_1;
}

