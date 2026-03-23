
undefined4 * __thiscall FUN_0046fcf0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_004e96d0(param_2,param_3);
  *param_1 = APC::vftable;
  param_1[6] = APC::vftable;
  param_1[0x8a] = 0;
  param_1[0xc0] = *(undefined4 *)(param_3 + 0x5fc);
  param_1[0xc1] = 0;
  param_1[0xc2] = 0;
  return param_1;
}

