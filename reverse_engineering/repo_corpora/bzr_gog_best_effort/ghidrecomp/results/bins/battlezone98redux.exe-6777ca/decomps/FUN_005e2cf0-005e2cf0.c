
undefined4 * __thiscall FUN_005e2cf0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_005a79f0(param_2,param_3);
  *param_1 = Torpedo::vftable;
  param_1[6] = Torpedo::vftable;
  param_1[0x8c] = *(undefined4 *)(param_3 + 0x18c);
  return param_1;
}

