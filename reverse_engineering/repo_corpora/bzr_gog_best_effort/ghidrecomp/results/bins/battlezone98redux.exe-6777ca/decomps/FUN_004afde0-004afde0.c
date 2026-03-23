
uint FUN_004afde0(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  
  pbVar1 = param_1 + param_2;
  for (; param_1 < pbVar1; param_1 = param_1 + 1) {
    param_3 = param_3 << 8 ^ *(uint *)(&DAT_008e7ca0 + (param_3 >> 0x18 ^ (uint)*param_1) * 4);
  }
  return ~param_3;
}

