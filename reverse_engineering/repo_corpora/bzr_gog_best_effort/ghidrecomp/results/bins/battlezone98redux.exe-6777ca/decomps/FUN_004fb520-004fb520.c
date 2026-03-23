
void FUN_004fb520(int param_1,int param_2)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = (float)((*(double *)(param_2 + 0x178) + *(double *)(param_2 + 400)) * 0.5 -
                 *(double *)(param_2 + 0x160));
  fVar3 = (float)((*(double *)(param_2 + 0x188) + *(double *)(param_2 + 0x1a0)) * 0.5 -
                 *(double *)(param_2 + 0x170));
  fVar1 = (float10)FUN_00820570((double)(fVar2 * fVar2 + fVar3 * fVar3));
  *(float *)(param_1 + 0x14) = -(fVar3 * (float)fVar1);
  *(float *)(param_1 + 0x18) = fVar2 * (float)fVar1;
  *(float *)(param_1 + 4) = (float)*(double *)(*(int *)(param_1 + 0x1038) + 0x48);
  *(float *)(param_1 + 8) = (float)*(double *)(param_2 + 0x168) + 100.0;
  *(float *)(param_1 + 0xc) = (float)*(double *)(*(int *)(param_1 + 0x1038) + 0x58);
  return;
}

