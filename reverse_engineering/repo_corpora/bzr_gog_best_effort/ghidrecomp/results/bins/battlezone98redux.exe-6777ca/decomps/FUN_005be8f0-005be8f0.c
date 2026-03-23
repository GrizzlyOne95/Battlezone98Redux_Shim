
undefined4 * __thiscall FUN_005be8f0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004e96d0(param_2,param_3);
  *param_1 = SAV::vftable;
  param_1[6] = SAV::vftable;
  param_1[0x8a] = 1;
  param_1[0xc0] = *(undefined4 *)(param_1[0x3e] + 0x5f0);
  return param_1;
}

