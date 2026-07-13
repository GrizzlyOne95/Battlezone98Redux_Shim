
undefined4 * __thiscall FUN_005b0c80(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_005111f0(param_2,param_3);
  *param_1 = ProximityMine::vftable;
  param_1[6] = ProximityMine::vftable;
  param_1[0x90] = *(undefined4 *)(param_3 + 0x16c);
  return param_1;
}

