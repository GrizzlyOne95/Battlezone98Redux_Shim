
undefined4 * __thiscall FUN_0047cb50(undefined4 *param_1,int param_2,int param_3)

{
  float10 fVar1;
  
  FUN_004802c0(param_2,param_3);
  *param_1 = Bolt::vftable;
  fVar1 = (float10)FUN_00417910(*(float *)(param_3 + 0x7c) * *(float *)(param_3 + 0x7c) * 0.25 +
                                *(float *)(param_3 + 0x80) * *(float *)(param_3 + 0x80) +
                                *(float *)(param_3 + 0x78) * *(float *)(param_3 + 0x78));
  param_1[0x40] = (float)fVar1;
  if (*(int *)(param_2 + 100) == 0) {
    *(undefined4 *)(param_2 + 0xac) = *(undefined4 *)(param_3 + 0x78);
  }
  return param_1;
}

