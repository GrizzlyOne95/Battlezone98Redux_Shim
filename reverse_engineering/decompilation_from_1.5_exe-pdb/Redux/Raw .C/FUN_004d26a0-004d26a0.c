
undefined4 * __thiscall FUN_004d26a0(undefined4 *param_1,int param_2,int param_3)

{
  FUN_004802c0(param_2,param_3);
  *param_1 = FlamePuff::vftable;
  *(undefined4 *)(param_2 + 0xac) = *(undefined4 *)(param_3 + 0x78);
  return param_1;
}

