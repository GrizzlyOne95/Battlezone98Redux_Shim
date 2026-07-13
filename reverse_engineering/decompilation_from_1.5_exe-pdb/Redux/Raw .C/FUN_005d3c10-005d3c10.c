
undefined4 * __thiscall FUN_005d3c10(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0047e9c0(param_2,param_3);
  *param_1 = ScrapSilo::vftable;
  param_1[6] = ScrapSilo::vftable;
  param_1[0x8e] = 0xffffffff;
  param_1[0x8f] = 0;
  return param_1;
}

