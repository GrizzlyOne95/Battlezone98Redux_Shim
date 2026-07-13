
int * __thiscall
FUN_0050d630(int param_1,int *param_2,float param_3,undefined4 param_4,float param_5)

{
  float fVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x14);
  fVar1 = *(float *)(param_1 + 0xc);
  *param_2 = (int)((float)*(int *)(param_1 + 0x10) + param_3 * *(float *)(param_1 + 0xc));
  param_2[1] = (int)((float)iVar2 - param_5 * fVar1);
  return param_2;
}

