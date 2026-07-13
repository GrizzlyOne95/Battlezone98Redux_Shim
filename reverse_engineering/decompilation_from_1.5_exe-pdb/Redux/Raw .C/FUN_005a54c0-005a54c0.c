
undefined4 * __thiscall
FUN_005a54c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  FUN_004e58d0(param_2,param_3);
  *param_1 = PersonGetIn::vftable;
  param_1[0x50] = *param_4;
  param_1[0x51] = param_4[1];
  param_1[0x52] = param_4[2];
  *(undefined4 *)(*(int *)(param_1[0x4d] + 8) + -8 + *(int *)(param_1[0x4d] + 4) * 8) = *param_4;
  *(undefined4 *)(*(int *)(param_1[0x4d] + 8) + -4 + *(int *)(param_1[0x4d] + 4) * 8) = param_4[2];
  return param_1;
}

