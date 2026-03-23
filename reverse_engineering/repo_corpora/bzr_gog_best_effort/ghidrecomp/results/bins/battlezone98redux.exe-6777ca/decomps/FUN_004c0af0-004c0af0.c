
void __thiscall FUN_004c0af0(int param_1,float *param_2)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xf4);
  dVar1 = *(double *)(iVar3 + 0x50);
  dVar2 = *(double *)(iVar3 + 0x58);
  *param_2 = (float)*(double *)(iVar3 + 0x48);
  param_2[1] = (float)dVar1;
  param_2[2] = (float)dVar2;
  FUN_0083e885();
  return;
}

