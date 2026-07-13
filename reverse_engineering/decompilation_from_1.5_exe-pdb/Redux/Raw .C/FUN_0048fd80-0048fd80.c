
undefined4 * __thiscall FUN_0048fd80(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_0048eda0(param_2,param_3);
  *param_1 = ChargeGun::vftable;
  param_1[0x38] = 0;
  param_1[0x3a] = *(undefined4 *)(param_3 + 0xac);
  param_1[0x3b] = *(int *)(param_3 + 0xa8) * 0x2c + *(int *)(param_3 + 0xac);
  param_1[0x39] = param_1[0x3a];
  param_1[3] = *(undefined4 *)(param_1[0x39] + 0x20);
  param_1[0x2c] = *(undefined4 *)(param_1[0x39] + 0x28);
  if (*(float *)(param_1[0x39] + 8) == 0.0) {
    param_1[0x2c] = param_1[0x2c] * *(int *)(param_1[0x39] + 4);
  }
  param_1[0x3c] = 0;
  return param_1;
}

