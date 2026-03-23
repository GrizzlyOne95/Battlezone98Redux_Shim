
int * __thiscall FUN_006da2f0(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  *param_1 = iVar1;
  param_1[1] = iVar1 >> 0x1f;
  return param_1;
}

