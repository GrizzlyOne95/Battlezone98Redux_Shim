
void FUN_00439de0(float *param_1,int param_2)

{
  double dVar1;
  double dVar2;
  
  dVar1 = *(double *)(param_2 + 0x30);
  dVar2 = *(double *)(param_2 + 0x38);
  *param_1 = (float)*(double *)(param_2 + 0x28);
  param_1[1] = (float)dVar1;
  param_1[2] = (float)dVar2;
  FUN_0083e885();
  return;
}

