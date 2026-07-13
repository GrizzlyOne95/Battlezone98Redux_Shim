
float10 FUN_005d2ab0(int param_1,int param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)FUN_007855e0((double)*(float *)(param_1 + 8),(double)*(float *)(param_1 + 0xc));
  fVar2 = (float10)FUN_007855e0((double)*(float *)(param_2 + 8),(double)*(float *)(param_2 + 0xc));
  return (float10)((float)fVar2 - (float)fVar1);
}

