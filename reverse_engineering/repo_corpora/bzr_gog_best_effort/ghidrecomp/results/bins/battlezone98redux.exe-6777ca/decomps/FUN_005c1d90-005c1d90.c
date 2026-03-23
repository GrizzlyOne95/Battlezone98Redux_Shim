
undefined4 * __thiscall FUN_005c1d90(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_004e96d0(param_2,param_3);
  *param_1 = Scavenger::vftable;
  param_1[6] = Scavenger::vftable;
  param_1[0xc0] = *(undefined4 *)(param_3 + 0x5f0);
  param_1[0xc1] = 0;
  param_1[0x8a] = 0;
  param_1[0xc2] = 0xffffffff;
  param_1[0xc3] = 0;
  return param_1;
}

