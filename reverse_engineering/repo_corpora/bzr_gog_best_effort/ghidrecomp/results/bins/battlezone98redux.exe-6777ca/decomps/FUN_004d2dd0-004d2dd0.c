
undefined4 * __thiscall FUN_004d2dd0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_005111f0(param_2,param_3);
  *param_1 = FlareMine::vftable;
  param_1[6] = FlareMine::vftable;
  param_1[0x90] = 0;
  param_1[0x91] = *(uint *)(param_3 + 0x17c) ^ 0x80000000;
  return param_1;
}

