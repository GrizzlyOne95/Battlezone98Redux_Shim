
void FUN_00821f00(int param_1,int *param_2,int *param_3,int *param_4,undefined4 param_5)

{
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (float)*param_2 * 0.01;
  local_10 = (float)*param_3 * 0.01;
  local_c = (float)*param_4 * 0.01;
  FUN_00820180(&local_14,&local_14,1,param_1 + 0x20);
  FUN_00821c50(param_5,&local_14);
  DAT_00946738 = 0;
  DAT_0094673c = 0;
  DAT_00946740 = 9;
  FUN_0083e885();
  return;
}

