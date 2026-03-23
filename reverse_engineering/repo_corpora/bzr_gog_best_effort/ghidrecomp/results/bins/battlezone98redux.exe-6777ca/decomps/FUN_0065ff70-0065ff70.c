
undefined4 * __thiscall FUN_0065ff70(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_0047e9c0(param_2,param_3);
  *param_1 = Portal::vftable;
  param_1[6] = Portal::vftable;
  param_1[0x8e] = *(undefined4 *)(param_3 + 0x160);
  param_1[0x91] = 0;
  param_1[0x8f] = 0;
  param_1[0x90] = 0;
  *(undefined1 *)(param_1 + 0x92) = 0;
  param_1[0x93] = 0;
  return param_1;
}

