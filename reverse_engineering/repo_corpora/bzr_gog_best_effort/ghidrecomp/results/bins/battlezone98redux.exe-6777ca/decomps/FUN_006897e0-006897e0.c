
void FUN_006897e0(float *param_1,int param_2,double param_3,double param_4,double param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  
  fVar1 = *(float *)(param_2 + 0x44);
  fVar2 = *(float *)(param_2 + 0x50);
  fVar3 = *(float *)(param_2 + 0x5c);
  dVar7 = *(double *)(param_2 + 0x70);
  fVar4 = *(float *)(param_2 + 0x48);
  fVar5 = *(float *)(param_2 + 0x54);
  fVar6 = *(float *)(param_2 + 0x60);
  dVar8 = *(double *)(param_2 + 0x78);
  *param_1 = (float)((double)*(float *)(param_2 + 0x40) * param_3 +
                     (double)*(float *)(param_2 + 0x4c) * param_4 +
                     (double)*(float *)(param_2 + 0x58) * param_5 + *(double *)(param_2 + 0x68));
  param_1[1] = (float)((double)fVar1 * param_3 + (double)fVar2 * param_4 + (double)fVar3 * param_5 +
                      dVar7);
  param_1[2] = (float)((double)fVar4 * param_3 + (double)fVar5 * param_4 + (double)fVar6 * param_5 +
                      dVar8);
  FUN_0083e885();
  return;
}

