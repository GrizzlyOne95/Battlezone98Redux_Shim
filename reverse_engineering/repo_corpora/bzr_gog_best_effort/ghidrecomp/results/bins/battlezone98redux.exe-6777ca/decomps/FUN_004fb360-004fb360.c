
void FUN_004fb360(int param_1,int param_2)

{
  double dVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  
  fVar3 = (float)((*(double *)(param_2 + 0x178) + *(double *)(param_2 + 400)) * 0.5 -
                 *(double *)(param_2 + 0x160));
  fVar4 = (float)((*(double *)(param_2 + 0x188) + *(double *)(param_2 + 0x1a0)) * 0.5 -
                 *(double *)(param_2 + 0x170));
  fVar2 = (float10)FUN_00820570((double)(fVar3 * fVar3 + fVar4 * fVar4));
  *(float *)(param_1 + 0x14) = -(fVar4 * (float)fVar2);
  *(float *)(param_1 + 0x18) = fVar3 * (float)fVar2;
  dVar1 = *(double *)(param_2 + 0x160);
  fVar2 = (float10)FUN_004a7890();
  *(float *)(param_1 + 4) = (float)dVar1 + (float)fVar2 * DAT_009b7cc0;
  *(float *)(param_1 + 8) = (float)*(double *)(param_2 + 0x168) + 100.0;
  dVar1 = *(double *)(param_2 + 0x170);
  fVar2 = (float10)FUN_004a7890();
  *(float *)(param_1 + 0xc) = (float)dVar1 + (float)fVar2 * DAT_009b7cc0;
  return;
}

