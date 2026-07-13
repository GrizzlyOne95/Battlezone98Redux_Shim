
void FUN_00775800(int param_1,int param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_004588c0((float)*(int *)(param_1 + 0x20));
  *(float *)(param_1 + 0x14) =
       ((float)fVar1 - (float)*(int *)(param_1 + 0x20) * 0.5) + (float)*(double *)(param_2 + 0x160);
  fVar1 = (float10)FUN_004588c0((float)*(int *)(param_1 + 0x20));
  *(float *)(param_1 + 0x1c) =
       ((float)fVar1 - (float)*(int *)(param_1 + 0x20) * 0.5) + (float)*(double *)(param_2 + 0x170);
  return;
}

