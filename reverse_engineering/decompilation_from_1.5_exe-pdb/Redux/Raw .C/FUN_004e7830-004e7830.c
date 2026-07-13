
undefined4 * __thiscall FUN_004e7830(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004e6bf0(param_2,param_3,0x40c00000);
  *param_1 = GoGet::vftable;
  param_1[0x3f] = 0x40a00000;
  param_1[0x1b] = 0x3f800000;
  return param_1;
}

