
void FUN_00497780(undefined4 param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00820180(&local_14,param_1,1,param_2 + 0x10);
  if (local_c <= 1.0) {
    fVar1 = param_2[2] * local_14 + *param_2;
    fVar2 = param_2[3] * local_10 + param_2[1];
  }
  else {
    fVar1 = (param_2[2] * local_14) / local_c + *param_2;
    fVar2 = (param_2[3] * local_10) / local_c + param_2[1];
  }
  if (param_3 != (float *)0x0) {
    if (local_c == 0.0) {
      *param_3 = 1e+30;
    }
    else {
      *param_3 = param_2[2] / local_c;
    }
  }
  FUN_0083e885((int)fVar1,(int)fVar2);
  return;
}

