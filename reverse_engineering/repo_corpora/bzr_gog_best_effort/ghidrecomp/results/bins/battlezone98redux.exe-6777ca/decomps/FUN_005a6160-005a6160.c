
undefined4 * __thiscall FUN_005a6160(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_004c9a10(param_2,param_3);
  *param_1 = PlanarExplosion::vftable;
  param_1[0xe] = ((*(float *)(param_3 + 0x50) - *(float *)(param_3 + 0x3c)) *
                 *(float *)(param_3 + 0x38)) / (float)*(int *)(param_3 + 0x34);
  return param_1;
}

