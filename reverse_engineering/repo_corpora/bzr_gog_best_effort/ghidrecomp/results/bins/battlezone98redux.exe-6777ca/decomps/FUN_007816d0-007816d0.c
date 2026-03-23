
byte FUN_007816d0(float *param_1,float *param_2,float *param_3,float *param_4)

{
  byte bVar1;
  
  bVar1 = ((uint)((param_1[2] * param_2[1] - param_1[1] * param_2[2]) * *param_3 +
                  (*param_1 * param_2[2] - param_1[2] * *param_2) * param_3[1] +
                 (param_1[1] * *param_2 - *param_1 * param_2[1]) * param_3[2]) & 0x80000000) != 0;
  if (((uint)((param_1[2] * param_3[1] - param_1[1] * param_3[2]) * *param_4 +
              (*param_1 * param_3[2] - param_1[2] * *param_3) * param_4[1] +
             (param_1[1] * *param_3 - *param_1 * param_3[1]) * param_4[2]) & 0x80000000) != 0) {
    bVar1 = bVar1 | 2;
  }
  return bVar1;
}

