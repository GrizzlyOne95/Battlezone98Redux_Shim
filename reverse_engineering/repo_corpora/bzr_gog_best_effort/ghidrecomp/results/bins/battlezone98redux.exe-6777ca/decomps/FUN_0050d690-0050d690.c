
float * __thiscall FUN_0050d690(int param_1,float *param_2,int param_3,int param_4)

{
  float fVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x14);
  fVar1 = *(float *)(param_1 + 0xc);
  *param_2 = (float)(param_3 - *(int *)(param_1 + 0x10)) / *(float *)(param_1 + 0xc);
  param_2[1] = (float)(iVar2 - param_4) / fVar1;
  return param_2;
}

