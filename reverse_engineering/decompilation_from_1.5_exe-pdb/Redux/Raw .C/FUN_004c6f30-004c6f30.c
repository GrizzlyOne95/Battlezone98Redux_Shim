
void __thiscall FUN_004c6f30(undefined4 param_1,int *param_2,undefined4 param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00820180(&local_14,param_3,1,param_4 + 0x10,param_1);
  if (local_c <= 1.0) {
    fVar1 = param_4[2] * local_14 + *param_4;
    fVar2 = param_4[3] * local_10 + param_4[1];
  }
  else {
    fVar1 = (param_4[2] * local_14) / local_c + *param_4;
    fVar2 = (param_4[3] * local_10) / local_c + param_4[1];
  }
  local_18 = (int)fVar2;
  local_1c = (int)fVar1;
  *param_2 = local_1c;
  param_2[1] = local_18;
  FUN_0083e885();
  return;
}

