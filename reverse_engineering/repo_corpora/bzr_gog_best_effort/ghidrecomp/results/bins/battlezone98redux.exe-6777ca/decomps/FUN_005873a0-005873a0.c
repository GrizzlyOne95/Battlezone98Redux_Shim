
void __thiscall FUN_005873a0(int param_1,float *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xf4);
  *(double *)(iVar1 + 0x48) = (double)*param_2;
  *(double *)(iVar1 + 0x50) = (double)param_2[1];
  *(double *)(iVar1 + 0x58) = (double)param_2[2];
  FUN_004db100();
  return;
}

