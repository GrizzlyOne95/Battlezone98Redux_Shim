
void FUN_00820180(float *param_1,float *param_2,int param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  while (param_3 = param_3 + -1, -1 < param_3) {
    fVar1 = *param_2;
    fVar2 = param_2[1];
    fVar3 = param_2[2];
    *param_1 = (float)((double)(*param_4 * fVar1 + param_4[3] * fVar2 + param_4[6] * fVar3) +
                      *(double *)(param_4 + 10));
    param_1[1] = (float)((double)(param_4[1] * fVar1 + param_4[4] * fVar2 + param_4[7] * fVar3) +
                        *(double *)(param_4 + 0xc));
    param_1[2] = (float)((double)(param_4[2] * fVar1 + param_4[5] * fVar2 + param_4[8] * fVar3) +
                        *(double *)(param_4 + 0xe));
    param_2 = param_2 + 3;
    param_1 = param_1 + 3;
  }
  return;
}

