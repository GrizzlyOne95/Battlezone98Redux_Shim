
undefined4 * __thiscall FUN_005b2d40(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_005abab0(param_2,param_3);
  *param_1 = Recycler::vftable;
  param_1[6] = Recycler::vftable;
  param_1[0xdc] = 0xffffffff;
  param_1[0xdd] = 0;
  return param_1;
}

